#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class TCPClient; }
QT_END_NAMESPACE

class TCPClient : public QMainWindow
  {
  Q_OBJECT

  public:
    TCPClient(QWidget *parent = nullptr);
    ~TCPClient();

  private slots:
    void on_theConnectBtn_pressed();
    void on_theConnectBtn_released();

    void on_theSendBtn_pressed();
    void on_theSendBtn_released();

    void on_theExplorerWnd_pressed();

private:
    Ui::TCPClient *theUi;
    int theFd = -1;

    bool isConnected() const { return theFd != -1; };
    bool isAddressSet();
    void closeSocket();
    void resetSocket();
    bool connectToServer();
    int send(char *aBuffer, const int aSize);
  };

#endif // TCPCLIENT_H
