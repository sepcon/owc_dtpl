#include <wa_api_invoke_method.h>

#include <iostream>
#include <map>
#include <optional>
#include <string>

#include "collector.h"

using namespace dtpl;

json_type getAntivirus() { return "antivirus"; }

int main() {
  using namespace std;
  // clang-format off
    dtpl::data_template conf = {
        "anti_malware"_key <<= getAntivirus,
        "name" <<= oesis_method(0, "result/name"_p2string),
        "public_file_sharing" <<= oesis_method(0, "public_file_sharing_bool"_p2int),
        "public_file_sharing_bool" <<= oesis_method(0, "public_file_sharing_bool"_p2bai),
        "os_info" <<= oesis_method(WAAPI_MID_ABORT_INFECTION_SCAN_BY_ID, {
            "os_name" <<= "name"_p2string,
            "version" <<= "version"_p2string,
        }, method_input(json_type{})),

        "user_info"_key <<= {
            "public_sharing" <<= oesis_method(0, "public_sharing"_p2int),
            "name" <<= oesis_method(WAAPI_MID_GET_AGENT_STATE, "result/name"_p2int),
            "pass_protected" <<= oesis_method(WAAPI_MID_GET_AGENT_STATE, {
                "key" <<= "val"_p2bool,
                "key_int" <<= "val"_p2int,
                "key_object" <<= "bool"_p2bai,
            }),
        },
        "sub_other_key"_key <<= {
            "anti_phising" <<= callback(getAntivirus),
            "boolean" <<= callback(getAntivirus)
        },
        "anti_malware"_key <<= {
            "rtp" <<= oesis_method(WAAPI_MID_GET_RTP_STATE, "result/enabled"_p2bai)
        }
    };

  // clang-format on

  auto out = collector_base{}.collect(conf);
  cout << json_type{collector_base{}.collect(conf).value()}.dump() << endl;
  return 0;
}
