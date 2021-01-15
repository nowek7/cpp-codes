#include "TCPClient.h"
#include "ui_tcpclient.h"

#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>

#include <WinSock2.h>
#include <WS2tcpip.h>

TCPClient::TCPClient(QWidget *parent)
  :
  QMainWindow(parent),
  theUi(new Ui::TCPClient)
  {
  theUi->setupUi(this);
  theUi->theSendBtn->setEnabled(false);
  theUi->theMessageTextEdit->setEnabled(false);
  theUi->theExplorerWnd->setEnabled(false);
  theUi->theMessageTextEdit->clear();
  }

TCPClient::~TCPClient()
  {
  delete theUi;
  }

void TCPClient::closeSocket()
  {
  if (theFd != -1)
    {
    closesocket(theFd);
    WSACleanup();
    theFd = -1;
    }
  }

bool TCPClient::isAddressSet()
  {
  if (theUi->theHostTextEdit->toPlainText().isNull() ||
      theUi->thePortTextEdit->toPlainText().isNull())
    return false;

  if (theUi->theHostTextEdit->toPlainText().isEmpty() ||
      theUi->thePortTextEdit->toPlainText().isEmpty())
      return false;

  return true;
  }

bool TCPClient::connectToServer()
  {
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
    {
    WSACleanup();
    return false;
    }

  if (!isAddressSet())
    return false;

  int sock = -1;
  struct addrinfo hints{};
  struct addrinfo *server;
  auto port = theUi->thePortTextEdit->toPlainText().toUInt();

  sock = static_cast<int>(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
  if (sock < 0)
    {
    printf("Create TCP socket failed\n");
    return false;
    }

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  std::string host = theUi->theHostTextEdit->toPlainText().toStdString();
  int result = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &server);
  if (result != 0)
    {
    ::closesocket(sock);
    freeaddrinfo(server);
    }

  result = ::connect(sock, server->ai_addr, static_cast<int>(server->ai_addrlen));
  freeaddrinfo(server);
  if (result < 0)
    {
    if (errno == EINPROGRESS)
      return true;
    else
      return false;
    }

  theFd = sock;

  int optval = 1;
  if (setsockopt(theFd, SOL_SOCKET, SO_KEEPALIVE, reinterpret_cast<char*>(&optval), sizeof(optval)) == -1)
    {
    printf("setsockopt - SO_KEEPALIVE");
    return false;
    }

  return true;
  }

int TCPClient::send(char *aBuffer, const int aSize)
  {
  return ::send(theFd, aBuffer, aSize, 0);
  }

void TCPClient::on_theConnectBtn_pressed()
  {
  theUi->theHostTextEdit->setEnabled(false);
  theUi->thePortTextEdit->setEnabled(false);
  theUi->theConnectBtn->setEnabled(false);
  }

void TCPClient::on_theConnectBtn_released()
  {
  const auto text = theUi->theConnectBtn->text();
  if (text == "Połącz")
    {
    bool connected = connectToServer();
    if (connected)
      {
      theUi->theConnectBtn->setText("Rozłącz");
      theUi->theMessageTextEdit->setEnabled(true);
      theUi->theSendBtn->setEnabled(true);
      theUi->theExplorerWnd->setEnabled(true);
      }
    else
      {
      QMessageBox msgBox;
      msgBox.setText("Nie można połączyć się z serwerem! \n Sprawdź host i port.");
      msgBox.exec();
      }
    }
  else
    closeSocket();

  if (!isConnected())
    {
    theUi->theHostTextEdit->setEnabled(true);
    theUi->thePortTextEdit->setEnabled(true);
    theUi->theConnectBtn->setText("Połącz");

    theUi->theMessageTextEdit->clear();
    theUi->theMessageTextEdit->setEnabled(false);
    theUi->theExplorerWnd->setEnabled(false);
    theUi->theSendBtn->setEnabled(false);
    }

  theUi->theConnectBtn->setEnabled(true);
  }

void TCPClient::on_theSendBtn_pressed()
  {
  theUi->theMessageTextEdit->setEnabled(false);
  theUi->theSendBtn->setEnabled(false);
  }

void TCPClient::on_theSendBtn_released()
  {
  QMessageBox msgBox;
  QString errMsg = "Nie udało się wysłać wiadomości!\n Rozłącz się i połącz się ponownie z serwerem.";

  const auto msg = theUi->theMessageTextEdit->toPlainText().toStdString();
  int length = static_cast<int>(msg.length());
  int writeBytes = send(reinterpret_cast<char*>(&length), sizeof(length));
  if (writeBytes < 0)
    {
    msgBox.setText(errMsg);
    msgBox.exec();
    return;
    }

  writeBytes = send(const_cast<char*>(msg.c_str()), length);
  if (writeBytes < 0)
    {
    msgBox.setText(errMsg);
    msgBox.exec();
    return;
    }

  theUi->theMessageTextEdit->clear();
  theUi->theMessageTextEdit->clearFocus();
  theUi->theSendBtn->setEnabled(true);
  theUi->theMessageTextEdit->setEnabled(true);
  theUi->theExplorerWnd->setEnabled(true);

  msgBox.setText("Wysłano wiadomość!");
  msgBox.exec();
  }

void TCPClient::on_theExplorerWnd_pressed()
  {
  theUi->theMessageTextEdit->clear();
  auto fileName = QFileDialog::getOpenFileName(this,
                                               tr("Open file"), QDir::currentPath(), tr("Text files (*.txt)"));

  if (!QFile::exists(fileName))
    {
    QMessageBox msgBox;
    msgBox.setText(fileName + " - nie istnieje!");
    msgBox.exec();
    }

  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
    QMessageBox msgBox;
    msgBox.setText("Nie można otworzyć pliku - " + fileName);
    msgBox.exec();
    }

  QTextStream ifile(&file);
  ifile.setCodec("UTF-8");
  while (!ifile.atEnd())
    {
    QString line = ifile.readLine();
    theUi->theMessageTextEdit->append(line);
    }
  }
