# websocket_lite

<p>Linux/Mac <img src="https://travis-ci.org/smasherprog/websocket_lite.svg?branch=master"/><p>
<p>Windows <img src="https://ci.appveyor.com/api/projects/status/kqa94n7p8se05vi9/branch/master?svg=true"/><p>
<p>This library is a fully compliant websocket implementation! <a href="http://htmlpreview.github.io/?https://github.com/smasherprog/Projects_Setup/blob/master/websocket_lite/index.html">Autobahn complete </a>, but with a few design goals:

<ul>
<li>
Cross-platform: Asio https://github.com/chriskohlhoff/asio/
</li>
<li>
Performance 
</li>
<li>
Simple and easy to use
</li>
<li>
Latest standards: c++ 17 
</li>
<li>
All functions are thread-safe and can be called from any thread at any time
</li>
</ul>

<h3>Dependencies: Cmake, openssl, zlib</h3>
<ul>
<li>
Ubuntu: sudo apt-get install libssl-dev zlib1g-dev -y
</li>
<li>
Mac: brew install openssl zlib
</li>
<li>
WIndows: vcpkg install openssl zlib
</li>
</ul>

<h2>USAGE</h2>
<p>To get started check out the example here<p>
https://github.com/smasherprog/websocket_lite/blob/master/Test/main.cpp

```c++

SL::WS_LITE::PortNumber port(3002);
auto listener =
  SL::WS_LITE::CreateContext(SL::WS_LITE::ThreadCount(1))
    ->NoTLS()
    ->CreateListener(port)
    ->onConnection([&](const std::shared_ptr<SL::WS_LITE::IWSocket> &socket, const std::unordered_map<std::string, std::string> &header) {
 
    })
    ->onMessage([&](const std::shared_ptr<SL::WS_LITE::IWSocket> &socket, const SL::WS_LITE::WSMessage &message) {

    })->listen();
    listener->set_ReadTimeout(std::chrono::seconds(100));
    listener->set_WriteTimeout(std::chrono::seconds(100));
    
auto clientctx =
  SL::WS_LITE::CreateContext(SL::WS_LITE::ThreadCount(1))
    ->NoTLS()
    ->CreateClient()
    ->onConnection([&](const std::shared_ptr<SL::WS_LITE::IWSocket> &socket, const std::unordered_map<std::string, std::string> &header) {

    })
    ->onDisconnection([&](const std::shared_ptr<SL::WS_LITE::IWSocket> &socket, unsigned short code, const std::string &msg) {
    })->connect("localhost", port);

```
