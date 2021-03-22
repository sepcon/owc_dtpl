
//#include <iostream>
//#include <variant>
//using namespace std;
//using std::string;
//using json_type = std::string;
//using DataCollectionCallback = std::function<json_type(const json_type& config)>;
//struct CategoryConfig;
//using CategoriesConfig = std::map<string, CategoryConfig>;
//using SubCategoriesConfig = std::map<string, CategoryConfig>;

//static DataCollectionCallback CollectNothing;

//using CatsConfigMap = std::map<string, string>;

//enum CatsConfigType { Object, OesisProducts };

//template <CatsConfigType type>
//struct Accepter;

//struct CatDataCollectorIF {
//  virtual void visit(Accepter<Object>&) = 0;
//  virtual void visit(Accepter<OesisProducts>&) = 0;
//};

//struct CatsConfigBase : public CatsConfigMap {
//  using Base = CatsConfigMap;
//  using Base::Base;
//  using Base::operator=;
//  virtual void accept(CatDataCollectorIF* collector) = 0;
//  virtual ~CatsConfigBase() = default;
//};

//template <CatsConfigType type>
//struct Accepter : public CatsConfigBase {
//  using Base = CatsConfigBase;
//  using Base::Base;
//  using Base::operator=;
//  void accept(CatDataCollectorIF* collector) override {
//    collector->visit(*this);
//  }
//};

//using OesisProductsConfig = Accepter<OesisProducts>;
//using CatsConfigObject = Accepter<Object>;

//using CatConfig = variant<OesisProductsConfig, CatsConfigObject>;


//struct DataCollector : public CatDataCollectorIF {
//  void visit(Accepter<Object>& object) override {
//    cout << "Visiting object..." << endl;
//    for (auto& [key, val] : object) {
//      cout << key << endl;
//    }
//  }
//  void visit(Accepter<OesisProducts>& array) override {
//    cout << "Visiting array..." << endl;
//    for (auto& [key, val] : array) {
//      cout << key << endl;
//    }
//  }
//};


//int main_()
//{
//    DataCollector d;
//    CatConfig cc = CatsConfigObject{{"hello", "world"}, {"bello", "world"}};


//    visit([&d](auto&& v) {
//        d.visit(v);
//    }, cc);
//    return 0;
//}

//struct CategoryConfig {
//  string enabledConfigPath = "config/option/enabled";
//  std::variant<DataCollectionCallback, SubCategoriesConfig> subCategoriesConfig;
//};

//json_type detectRTP(const json_type&) { return "detectRTP"; }
//json_type detectAntivirusEngine(const json_type&) { return "detectAntivirusEngine"; }
//json_type detectAntiphising(const json_type&) { return "detectAntiphising"; }
//json_type detectDeveloperTools(const json_type&) { return "detectDeveloperTools"; }
//json_type detectMediaPlayers(const json_type&) { return "detectMediaPlayers"; }
//json_type detectUninstallers(const json_type&) { return "detectUninstallers"; }
//json_type detectToolbars(const json_type&) { return "detectToolbars"; }
//json_type detectPublicFileSharing(const json_type&) { return "detectPublicFileSharing"; }
//json_type detectInstantMessegeners(const json_type&) {
//  return "detectInstantMessegeners";
//}
//json_type detectCleanerOptimizers(const json_type&) { return "detectCleanerOptimizers"; }
//json_type detectVPNClients(const json_type&) { return "detectVPNClients"; }
//json_type detectRemoteControls(const json_type&) { return "detectRemoteControls"; }
//json_type detectUnclassifiedPUAs(const json_type&) { return "detectUnclassifiedPUAs"; }
//json_type detectCloudStorages(const json_type&) { return "detectCloudStorages"; }

//using _sc = SubCategoriesConfig;
//using _cc = SubCategoriesConfig;

//_cc sohConfig = {
//    // compliance_check
//    {"Antivirus",
//     {"anti_malware/enabled",
//      SubCategoriesConfig{
//          {"rtp", {"rtp/enabled", detectRTP}},
//          {"signature_update", {"engine/enabled", detectAntivirusEngine}}}}},
//    {"Antiphishing", {"anti_phising/enabled", detectAntiphising}},

//    // app_removers
//    {"Developer_Tool", {"developer_tool/enabled", detectDeveloperTools}},
//    {"Media_Player", {"media_player/enabled", detectMediaPlayers}},
//    {"Uninstaller", {"uninstaller/enabled", detectUninstallers}},
//    {"Toolbars", {"toolbars/enabled", detectToolbars}},
//    {"PublicFileSharing",
//    {"public_files_haring/enabled", detectPublicFileSharing}},
//    {"Instant_Messegener",
//    {"instant_messegener/enabled", detectInstantMessegeners}},
//    {"Cleaner_Optimizer",
//    {"cleaner_optimizer/enabled", detectCleanerOptimizers}},
//    {"VPN_Client", {"vpn_client/enabled", detectVPNClients}},
//    {"Remote_Control", {"remote_control/enabled", detectRemoteControls}},
//    {"Unclassified_PUA", {"unclassified_pua/enabled", detectUnclassifiedPUAs}},
//    {"Cloud_Storage", {"cloud_storage/enabled", detectCloudStorages}},
//};

////#include <fstream>
////#include <iostream>
////#include <locale>
////#include <optional>
////#include <sstream>

////#include "di.hpp"

//// using namespace std;
//// using std::ostream;

//// namespace encryption {

//// void encode(ostream& os, const string_view& s) {
////  transform(s.begin(), s.end(), std::ostreambuf_iterator<char>(os),
////            [](char c) { return std::toupper(c, std::locale()); });
////}

//// template <class CharIterator>
//// optional<string> decode(CharIterator b, CharIterator e) {
////  string s;
////  transform(b, e, std::back_inserter(s),
////            [](char c) -> char { return std::tolower(c, {}); });
////  return s;
////}

//// optional<string> decode(istream& is) {
////  return decode(istream_iterator<char>{is}, istream_iterator<char>{});
////}

//// optional<string> decode(string_view view) {
////  return decode(view.begin(), view.end());
////}

////}  // namespace encryption

//// namespace di {
//// using namespace boost::di;
////}

//// class ILogger {
//// public:
////  virtual void log(const string& msg) = 0;
////};

//// class IDecrementor {
//// public:
////  virtual int subtract(int a, int b) = 0;
////};

//// class Security {
//// public:
////  Security(ILogger* logger) : logger_(logger) {}
////  void log(const string& msg) { logger_->log(msg); }

//// private:
////  ILogger* logger_ = nullptr;
////};

//// class Calculator {
//// public:
////  Calculator(IDecrementor* logger) : logger_(logger) {}
////  int subtract(int a, int b) { return logger_->subtract(a, b); }

//// private:
////  IDecrementor* logger_ = nullptr;
////};

//// class ConsoleLogger : public ILogger {
//////    ConsoleLogger();
////  void log(const string& s) override { cout << s << endl; }
////};

//// class NormalDecrementor : public IDecrementor {
//// public:
////  int subtract(int a, int b) override { return a - b; }
////};

//// int main_(int argc, char* argv[]) {
////  auto injector =
////      di::make_injector(di::bind<ILogger>().to<ConsoleLogger>(),
////                        di::bind<IDecrementor>().to<NormalDecrementor>());

////  injector.create<Security>().log("hello world");
////  cout << injector.create<Calculator>().subtract(10, 20) << endl;
////  return 0;
////}

//// ConsoleLogger::ConsoleLogger() {
////    cout << "Console" << endl;
////}
