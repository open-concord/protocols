#include "../inc/csp.hpp"

#include <stdexcept>
#include <cstring>

struct sockaddr_in csp::_form(int port) {
  struct sockaddr_in _peer;

  int _peerfd = socket(this->cfamily, SOCK_STREAM, 0);
  if (_peerfd < 0) {
    throw std::logic_error("[CSP::FORM] COULD NOT CREATE SOCKET");
  }

  bzero((char*) &_peer, sizeof(_peer));

  _peer.sin_family = AF_INET;
  if (port > 0) {_peer.sin_port = htons(port);}

  this->sockfd = _peerfd;
  return _peer;
}

void csp::target(tf_struct target) {
  struct hostent* s;

  s = gethostbyname(target.addr.c_str());
  if (s == NULL) {
    throw std::logic_error("[CSP::TARGET] COULD NOT FIND PEER's ADDR");
  }
  struct sockaddr_in _peer = this->_form(target.port);

  bcopy(
    (char*)s->h_addr,
    (char*)&_peer.sin_addr.s_addr,
    s->h_length
  );

  if (connect(
    this->sockfd,
    (struct sockaddr*) &_peer,
    (socklen_t) sizeof(_peer)
  ) < 0) {
    throw std::logic_error("[CSP::TARGET] COULD NOT CONNECT");
  };
  /** TODO: store _peer */
  this->self = _peer;
}

void csp::queue(int origin_fd) {
  struct sockaddr_in _in;
  socklen_t _inlen = sizeof(_in);
  int fd = accept(origin_fd, (struct sockaddr *) &_in, &_inlen);
  if (fd < 0) {
    throw std::logic_error("[CSP::QUEUE] COULD NOT ACCEPT");
  } else {
    this->sockfd = fd;
    this->self = _in;
  }
}

void csp::port(unsigned short int port) {
  struct sockaddr_in _info = this->_form(port);

  if (bind(this->sockfd, (struct sockaddr* ) &_info, sizeof(_info)) < 0) {
    throw std::logic_error("[CSP::PORT] COULD NOT BIND");
  }

  /** TODO: store _info */
  this->self = _info;
}

int csp::fd() {return this->sockfd;}

/** read (no status) */
std::string csp::readb() {
  /** read size header */
  char sh[4];
  bzero(sh, 4); // zero out buffer
  if (read(this->sockfd, &sh, 4) < 0) {
    throw std::logic_error("[CSP::READB] COULD NOT READ SIZE HEADER");
  }

  int s = atoi(sh)+4;
  char b[s];
  /** read message */
  bzero(b, s); // zero out buffer
  if (read(this->sockfd, &b, s) < 0) {
    throw std::logic_error("[CSP::READB] COULD NOT READ CONTENT BUFFER");
  }

  if (strlen(b) < 1) {
    throw std::logic_error("[CSP::READB] ZERO-LENGTH MESSAGE");
  }

  return std::string(b);
}

/** write (no status) */
void csp::writeb(std::string m) {
  if (m.length() < 1) {
    throw std::logic_error("[NP::WRITEB] ZERO-LENGTH MESSAGE");
  }
  /** 4 dec place size header */
  std::string so = std::to_string(m.size());
  while (so.size()<4) {
    so.insert(0, "0");
  }
  std::string o = so+m;
  if (write(this->sockfd, o.data(), o.size()) < 0) {
    throw std::logic_error("[CSP::WRITEB] COULD NOT WRITE");
  };
}

/** close (no status) */
void csp::closeb() {shutdown(this->sockfd, 2);}
