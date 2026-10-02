#include <stdexcept>
// JSON boundary only. Assessments and execution remain in the existing C++ engine.
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "analysis/ResponseAnalyzer.h"
#include "engine/TestRunner.h"
#include "engine/TestExecutionCoordinator.h"
#include "llm/MockLLM.h"
#include "models/TestRun.h"
#include "tests/InstructionOverrideTest.h"
#include "tests/PromptExtractionTest.h"
#include "tests/RoleManipulationTest.h"
#include "tests/ContextManipulationTest.h"
static std::string q(const std::string& s){std::ostringstream o;o<<'"';for(unsigned char c:s){switch(c){case '"':o<<"\\\"";break;case '\\':o<<"\\\\";break;case '\n':o<<"\\n";break;case '\r':o<<"\\r";break;case '\t':o<<"\\t";break;default:if(c<32)o<<"\\u"<<std::hex<<std::setw(4)<<std::setfill('0')<<int(c)<<std::dec;else o<<c;}}o<<'"';return o.str();}
static void meta(std::ostream& out,const InjectionTest& t){out<<"\"testId\":"<<t.getTestId()<<",\"testName\":"<<q(t.getTestName())<<",\"category\":"<<q(t.getCategory())<<",\"prompt\":"<<q(t.getPrompt())<<",\"expectedBehavior\":"<<q(t.getExpectedBehavior());}
static void ints(std::ostream& out,const std::vector<int>& v){out<<'[';for(size_t i=0;i<v.size();++i){if(i)out<<',';out<<v[i];}out<<']';}
std::string executeEngine(const std::string& op,int runId,const std::vector<int>& selected,const std::string* custom){std::ostringstream out;MockLLM llm;ResponseAnalyzer analyzer;TestRunner runner(analyzer);InstructionOverrideTest a(llm,10);PromptExtractionTest b(llm,20);RoleManipulationTest c(llm,30);ContextManipulationTest d(llm,40);std::vector<InjectionTest*> list={&a,&b,&c,&d};TestExecutionCoordinator::TestRegistry registry={{10,&a},{20,&b},{30,&c},{40,&d}};
 if(op=="catalog"){out<<"{\"modelName\":\"MockLLM\",\"tests\":[";for(size_t i=0;i<list.size();++i){if(i)out<<',';out<<'{';meta(out,*list[i]);out<<'}';}out<<"]}";return out.str();}
 if(custom)registry.at(selected.at(0))->setPrompt(*custom);
 TestExecutionCoordinator coordinator(runner);for(int id:selected){if(!coordinator.enqueueTestId(id))throw std::runtime_error("Queue is full");}TestRun run(runId,1);coordinator.executePendingTests(registry,run);
 out<<"{\"runId\":"<<runId<<",\"modelId\":1,\"modelName\":\"MockLLM\",\"backendConnected\":true,\"startedAt\":"<<q(run.getStartedAt())<<",\"completedAt\":"<<q(run.getCompletedAt())<<",\"totalTests\":"<<run.getTotalTests()<<",\"results\":[";
 auto resultIds=coordinator.getCreatedResultIds();for(size_t i=0;i<resultIds.size();++i){if(i)out<<',';const auto& r=*coordinator.findResult(resultIds[i]);out<<'{';meta(out,*registry.at(r.getTestId()));out<<",\"resultId\":"<<r.getResultId()<<",\"runId\":"<<r.getRunId()<<",\"response\":"<<q(r.getResponse())<<",\"status\":"<<q(r.getStatus())<<",\"severity\":"<<q(r.getSeverity())<<",\"analysis\":"<<q(r.getAnalysis())<<",\"executionTimeMs\":"<<std::setprecision(10)<<r.getExecutionTime()<<",\"timestamp\":"<<q(r.getTimestamp())<<'}';}
 out<<"],\"executedTestIds\":";ints(out,coordinator.getExecutedTestIds());out<<",\"invalidTestIds\":";ints(out,coordinator.getInvalidTestIds());out<<",\"resultIds\":";ints(out,resultIds);std::vector<int> sorted;coordinator.sortResultIds(ResultIdSortAlgorithm::Quick,&sorted);out<<",\"quickSortedResultIds\":";ints(out,sorted);std::vector<int> lifo;int popped=0;while(coordinator.popLatestResultId(&popped))lifo.push_back(popped);out<<",\"stackPopOrder\":";ints(out,lifo);out<<'}';return out.str();}
