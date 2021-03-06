/*
 * tcpServer.h
 *
 *  Created on: Jul 7, 2017
 *      Author: txh
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "tcpConnection.h"
#include "utility.h"


#include <map>
#include <memory>

class EventLoop;
class Acceptor;
class NetAddress;
class EventLoopThreadPool;

class TcpServer:public noncopyable{
public:
  TcpServer(EventLoop *loop, const NetAddress &addr);
  ~TcpServer();

  void start();
  void setConnectionCallBack(const ConnectionCallBack& cb);
  void setMessageCallBack(const MessageCallBack& cb);
  EventLoop* getLoop() const ;

  void setThreadNum(int numThreads);

private:
  void newConnection(int sockfd, const NetAddress &addr);
  void removeConnection(const TcpConnectionPtr& conn);
  void removeConnectionInLoop(const TcpConnectionPtr& conn);

  using TcpConnectMap = std::map<std::string,TcpConnectionPtr>;

  EventLoop *loop_;
  const std::string name_;
  std::shared_ptr<Acceptor> acceptor_;
  std::shared_ptr<EventLoopThreadPool> threadpoll_;
  ConnectionCallBack connectCallBack_;
  MessageCallBack messageCallBack_;
  bool started_;
  int nextConnId_;
  TcpConnectMap connects_;
};




#endif /* TCPSERVER_H_ */
