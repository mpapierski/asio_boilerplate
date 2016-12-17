#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#if defined(HAVE_FORK)
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#include "config.h"
#include "tcp_server.hpp"

int main(int argc, char* argv[]) {
  namespace po = boost::program_options;
  unsigned short port;
  po::options_description desc("Allowed options");
  desc.add_options()("help", "show help message")("version", "show version")
#if defined(HAVE_FORK)
      ("daemon", "daemonize")
#endif
          ("port,p", po::value<unsigned short>(&port)->required(), "port");
  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, desc), vm);
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }
  if (vm.count("version")) {
    std::cout << argv[0] << ' ' << PROJECT_VERSION << std::endl;
    return 0;
  }
  try {
    po::notify(vm);
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  boost::asio::io_service io_service;
#if defined(HAVE_FORK)
  if (vm.count("daemon")) {
    io_service.notify_fork(boost::asio::io_service::fork_prepare);

    pid_t pid = ::fork();
    if (pid > 0) {
      // Parent process, return and keep running
      return 0;
    } else if (pid == -1) {
      // Report error. Might be syslog call aswell.
      std::cerr << "fork #1 failed" << std::endl;
      std::exit(1);
    }

    // Make the process a new session leader. This detaches it from the
    // terminal.
    ::setsid();

    // A process inherits its working directory from its parent. This could be
    // on a mounted filesystem, which means that the running daemon would
    // prevent this filesystem from being unmounted. Changing to the root
    // directory avoids this problem.
    ::chdir("/");

    // The file mode creation mask is also inherited from the parent process.
    // We don't want to restrict the permissions on files created by the
    // daemon, so the mask is cleared.
    ::umask(0);

    // Service forks here
    pid = ::fork();
    if (pid > 0) {
      // Parent process, return and keep running
      std::exit(0);
    } else if (pid == -1) {
      std::cerr << "fork #2 failed" << std::endl;
      std::exit(1);
    }

    // Close the standard streams. This decouples the daemon from the terminal
    // that started it.
    ::close(0);
    ::close(1);
    ::close(2);

    // Inform the io_service that we have finished becoming a daemon. The
    // io_service uses this opportunity to create any internal file descriptors
    // that need to be private to the new process.
    io_service.notify_fork(boost::asio::io_service::fork_parent);
  }
#endif
  try {
    // Prepare server
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), port);
    tcp_server server(io_service, endpoint);
    server.start_accept();
    io_service.run();
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}