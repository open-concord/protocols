/** concord standard (network) protocol */
#pragma once

#include <protocols.hpp>

#include <string>

#ifdef __linux__ // linux
#include <sys/socket.h> // duh
#include <sys/types.h> // needed by socket.h
#include <netinet/in.h> // internet socket protocol
#include <strings.h> // bzero
#include <unistd.h> // close, accept, etc
#include <arpa/inet.h> // needed for ip ID
#include <netdb.h> // gethostbyname
#include <poll.h> // ppoll & poll
#endif


struct csp : public virtual np {
private:
  struct sockaddr_in _form(int port);
  struct sockaddr_in _peer;
public: 
  struct target_format {
    std::string addr;
    unsigned int port;
  };

  void queue(int origin_fd) override;
  void port(unsigned short int port) override;
  int fd() override;

  /** read (no status) */
  std::string readb() override;
  /** write (no status) */
  void writeb(std::string m) override;
  /** close (no status) */
  void closeb() override;
  csp(target_format target = {});
  ~csp() {}
};
