#include "vendor/httplib.h"
#include "vendor/json.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using json=nlohmann::json;
std::string executeEngine(const std::string&,int,const std::vector<int>&,const std::string*);
int main(int argc,char** argv){
 int port=8000;try{if(argc==3&&std::string(argv[1])=="--port")port=std::stoi(argv[2]);else if(argc!=1)throw std::runtime_error("Usage: tester_web [--port 8001]");if(port<1024||port>65535)throw std::runtime_error("Port must be 1024-65535");}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
 // CMake copies the web assets beside the executable, so it works from any cwd.
 const auto root=std::filesystem::absolute(argv[0]).parent_path()/"web";
 if(!std::filesystem::is_regular_file(root/"index.html")){std::cerr<<"Missing web assets beside executable. Rebuild with CMake.\n";return 1;}
 std::random_device random;std::ostringstream seed;for(int i=0;i<8;++i)seed<<std::hex<<random();const std::string token=seed.str();
 int runId=static_cast<int>(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())%1000000000);std::mutex lock;
 httplib::Server server;server.set_payload_max_length(32768);server.set_read_timeout(10,0);server.set_write_timeout(10,0);
 auto validHost=[&](const httplib::Request& r){const auto h=r.get_header_value("Host");return h=="127.0.0.1:"+std::to_string(port)||h=="localhost:"+std::to_string(port);};
 auto error=[](httplib::Response& r,int code,const std::string& message){r.status=code;r.set_content(json({{"error",message}}).dump(),"application/json");};
 server.set_pre_routing_handler([&](const httplib::Request& request,httplib::Response& response){if(!validHost(request)){error(response,403,"Use the local server URL.");return httplib::Server::HandlerResponse::Handled;}return httplib::Server::HandlerResponse::Unhandled;});
 server.set_post_routing_handler([](const httplib::Request&,httplib::Response& r){r.set_header("Cache-Control","no-store");r.set_header("X-Content-Type-Options","nosniff");r.set_header("Content-Security-Policy","default-src 'self'; script-src 'self'; style-src 'self'; connect-src 'self'; frame-ancestors 'none'; object-src 'none'");});
 server.Get("/api/health",[&](const httplib::Request&,httplib::Response& r){r.set_content(json({{"ok",true},{"modelName","MockLLM"},{"csrfToken",token}}).dump(),"application/json");});
 server.Get("/api/tests",[](const httplib::Request&,httplib::Response& r){r.set_content(executeEngine("catalog",0,{},nullptr),"application/json");});
 server.Post("/api/run",[&](const httplib::Request& request,httplib::Response& response){
 if(request.get_header_value("X-Lab-Token")!=token){error(response,403,"Refresh the local page before running a test.");return;}
 const auto origin=request.get_header_value("Origin");if(!origin.empty()&&origin!="http://127.0.0.1:"+std::to_string(port)&&origin!="http://localhost:"+std::to_string(port)){error(response,403,"Origin not allowed.");return;}
 try{const auto body=json::parse(request.body);if(!body.contains("testIds")||!body.at("testIds").is_array())throw std::runtime_error("Choose supported test IDs.");std::vector<int> ids;std::set<int> unique;for(const auto& id:body.at("testIds")){if(!id.is_number_integer())throw std::runtime_error("Test IDs must be integers.");int n=id.get<int>();if(n!=10&&n!=20&&n!=30&&n!=40)throw std::runtime_error("Unsupported test ID.");if(!unique.insert(n).second)throw std::runtime_error("Duplicate test ID.");ids.push_back(n);}if(ids.empty()||ids.size()>4)throw std::runtime_error("Choose one to four tests.");std::string custom;const std::string* prompt=nullptr;if(body.contains("customPrompt")){if(!body.at("customPrompt").is_string()||ids.size()!=1)throw std::runtime_error("Custom prompts need one technique.");custom=body.at("customPrompt").get<std::string>();if(custom.empty()||custom.size()>16000||custom.find('\0')!=std::string::npos||custom.find_first_not_of(" \t\r\n")==std::string::npos)throw std::runtime_error("Enter a nonempty custom prompt, up to 4000 characters.");prompt=&custom;}
 std::lock_guard<std::mutex> guard(lock);response.set_content(executeEngine("run",++runId,ids,prompt),"application/json");
 }catch(const std::exception& e){error(response,400,e.what());}});
 auto serve=[&](const std::string& route,const std::string& file,const std::string& mime){server.Get(route,[=](const httplib::Request&,httplib::Response& r){std::ifstream in(root/file,std::ios::binary);std::ostringstream text;text<<in.rdbuf();r.set_content(text.str(),mime);});};
 serve("/","index.html","text/html; charset=utf-8");serve("/app.js","app.js","text/javascript; charset=utf-8");serve("/style.css","style.css","text/css; charset=utf-8");
 std::cout<<"Open http://127.0.0.1:"<<port<<" . Ctrl+C stops the server.\n"<<std::flush;
 if(!server.listen("127.0.0.1",port)){std::cerr<<"Could not start server. Try --port 8001.\n";return 1;}return 0;
}
