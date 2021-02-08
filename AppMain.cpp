#include "AppMain.h"
#include "QtCGI.h"
#include "QEncryption.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <AppDefine.h>
#include <CkCrypt2.h>
#include <CkHttp.h>
#include <CkHttpResponse.h>
#include <CkHttpRequest.h>

#define KEY_PREFIX      "Congaubeo@123"

static QStringList fakeKeyList = QStringList() << "signInName"
                                               << "uaid"
                                               << "includeSuggestions"
                                               << "uiflvr"
                                               << "scid"
                                               << "hpgid"
                                               << "Signup_MemberNamePage_Client"
                                               << "evts"
                                               << "perf"
                                               << "data"
                                               << "navigation"
                                               << "type"
                                               << "redirectCount"
                                               << "timing"
                                               << "navigationStart"
                                               << "unloadEventStart"
                                               << "unloadEventEnd"
                                               << "redirectStart"
                                               << "redirectEnd"
                                               << "fetchStart"
                                               << "domainLookupStart"
                                               << "domainLookupEnd"
                                               << "connectStart"
                                               << "connectEnd"
                                               << "secureConnectionStart"
                                               << "requestStart"
                                               << "responseStart"
                                               << "responseEnd"
                                               << "domLoading"
                                               << "domInteractive"
                                               << "domContentLoadedEventStart"
                                               << "domContentLoadedEventEnd"
                                               << "domComplete"
                                               << "loadEventStart"
                                               << "loadEventEnd"
                                               << "customLoadEventEnd"
                                               << "entries"
                                               << "name"
                                               << "entryType"
                                               << "startTime"
                                               << "duration"
                                               << "initiatorType"
                                               << "nextHopProtocol"
                                               << "workerStart"
                                               << "transferSize"
                                               << "encodedBodySize"
                                               << "decodedBodySize"
                                               << "serverTiming"
                                               << "navigate"
                                               << "resource"
                                               << "link"
                                               << "script"
                                               << "h2"
                                               << "img"
                                               << "css"
                                               << "first"
                                               << "paint"
                                               << "contentful"
                                               << "connection"
                                               << "onchange"
                                               << "effectiveType"
                                               << "3g"
                                               << "rtt"
                                               << "downlink"
                                               << "saveData"
                                               << "tm"
                                               << "cm"
                                               << "tcxt"
                                               << "cntry"
                                               << "svr"
                                               << "dc"
                                               << "westus2"
                                               << "ri"
                                               << "wusXXXX000H"
                                               << "ver"
                                               << "v"
                                               << "rt"
                                               << "et"
                                               << "hst"
                                               << "signup"
                                               << "live"
                                               << "com"
                                               << "nt"
                                               << "av"
                                               << "pageApiId"
                                               << "clientDetails"
                                               << "country"
                                               << "userAction"
                                               << "source"
                                               << "PageView"
                                               << "clientTelemetryData"
                                               << "category"
                                               << "PageLoad"
                                               << "pageName"
                                               << "Signup_MemberNamePage"
                                               << "eventInfo"
                                               << "timestamp"
                                               << "perceivedPlt"
                                               << "networkLatency"
                                               << "appVersion"
                                               << "networkType"
                                               << "precaching"
                                               << "bundleVersion"
                                               << "deviceYear"
                                               << "isMaster"
                                               << "bundleHits"
                                               << "bundleMisses"
                                               << "btData"
                                               << "cxhFunctionRes"
                                               << "Signup_PasswordPage_Client"
                                               << "Signup_PasswordPage"
                                               << "Signup_ProfileAccrualPage_Client"
                                               << "Action_ClientSideTelemetry"
                                               << "Signup_ProfileAccrualPage"
                                               << "Signup_BirthdatePage_Client"
                                               << "Signup_BirthdatePage"
                                               << "Signup_HipPage_Client"
                                               << "Signup_HipPage"
                                               << "Timestamp"
                                               << "Timezone"
                                               << "PostStartTime"
                                               << "SessionID"
                                               << "PartnerId"
                                               << "Events"
                                               << "at"
                                               << "keydown"
                                               << "tid"
                                               << "MemberName"
                                               << "s"
                                               << "k"
                                               << "keyup"
                                               << "SubmitIndex"
                                               << "Browser"
                                               << "UserAgent"
                                               << "CookieEnabled"
                                               << "JavaEnabled"
                                               << "ScreenDepth"
                                               << "ScreenHeight"
                                               << "ScreenWidth"
                                               << "WindowHeight"
                                               << "WindowWidth"
                                               << "PageHeight"
                                               << "PageWidth"
                                               << "Language"
                                               << "Plugins"
                                               << "mousemove"
                                               << "dx"
                                               << "dy"
                                               << "x"
                                               << "y"
                                               << "click"
                                               << "LastName"
                                               << "b"
                                               << "focus"
                                               << "FirstName"
                                               << "CheckAvailStateMap"
                                               << "dajdfjoaiejrwer2342"
                                               << "hotmail"
                                               << "undefined"
                                               << "EvictionWarningShown"
                                               << "UpgradeFlowToken"
                                               << "MemberNameChangeCount"
                                               << "MemberNameAvailableCount"
                                               << "MemberNameUnavailableCount"
                                               << "CipherValue"
                                               << "SKI"
                                               << "BirthDate"
                                               << "Country"
                                               << "IsOptOutEmailDefault"
                                               << "IsOptOutEmailShown"
                                               << "IsOptOutEmail"
                                               << "LW"
                                               << "SiteId"
                                               << "IsRDM"
                                               << "WReply"
                                               << "ReturnUrl"
                                               << "SignupReturnUrl"
                                               << "SuggestedAccountType"
                                               << "OUTLOOK"
                                               << "SuggestionType"
                                               << "Locked"
                                               << "HFId"
                                               << "HType"
                                               << "visual"
                                               << "HSId"
                                               << "HId"
                                               << "HSol"
                                               << "acctcdn"
                                               << "hrcdn"
                                               << "vendor"
                                               << "common"
                                               << "pageLoadTime"
                                               << "msauth"
                                               << "acctcdnmsftuswe"
                                               << "FSSFZE"
                                               << "acctcdnvzeuno"
                                               << "device"
                                               << "DataRequest"
                                               << "fbundle"
                                               << "isProxy"
                                               << "OLfvCcbv"
                                               << "time_ms"
                                               << "WSQWA"
                                               << "hipTemplate"
                                               << "watsonestoppel"
                                               << "douglascrockford"
                                               << "ufeff"
                                               << "clientTelemetry"
                                               << "TimestampSecret"
                                               << "amtcxt"
                                               << "UnauthSessionId"
                                               << "Auryc"
                                               << "TelemetryContext"
                                               << "ApiRequest"
                                               << "MLuaF"
                                               << "ApiCall"
                                               << "LGseWNAB"
                                               << "responseText"
                                               << "credentials"
                                               << "trackDwellTime"
                                               << "HUBM"
                                               << "ResponseHeader"
                                               << "apiUseIpt"
                                               << "SKHD"
                                               << "correlationId"
                                               << "wlPreferIpt"
                                               << "hxRSU"
                                               << "view_time"
                                               << "apiCanary"
                                               << "DCZLE"
                                               << "WLXAccount"
                                               << "ClientPerf"
                                               << "batchTrack"
                                               << "sessionId"
                                               << "TsGr"
                                               << "cxhFunction"
                                               << "pageId"
                                               << "Qfrac"
                                               << "wutPOWE"
                                               << "UBQTR"
                                               << "TelemetryResourceBundle"
                                               << "ApiId"
                                               << "major"
                                               << "scuXXXX"
                                               << "facctcdnmsftuswe"
                                               << "XQZS"
                                               << "marchingAnts"
                                               << "GX"
                                               << "pwdless"
                                               << "TimeLoad"
                                               << "fclient"
                                               << "KGZU"
                                               << "fSessionID"
                                               << "UFE"
                                               << "ValidationBehavior"
                                               << "fservices"
                                               << "cnvCtrlBg"
                                               << "facctcdnvzeuno"
                                               << "ffwlink"
                                               << "EBZWQ"
                                               << "fLinkID"
                                               << "permission"
                                               << "JANR"
                                               << "memberNameType"
                                               << "EASI"
                                               << "CXH"
                                               << "IDPS"
                                               << "UnifiedHeader"
                                               << "CXHMBinary"
                                               << "YXVM"
                                               << "TimeClick"
                                               << "NASAKH"
                                               << "mktLocale"
                                               << "converged"
                                               << "msweb"
                                               << "messageHandle"
                                               << "SessionStorage"
                                               << "WizardExternal"
                                               << "VBCFZ"
                                               << "lwsignup"
                                               << "lrmen"
                                               << "iPageElt"
                                               << "GCPpM"
                                               << "hipContent"
                                               << "BNAX"
                                               << "TimePressed"
                                               << "CBU"
                                               << "signupTemplates"
                                               << "ESKN"
                                               << "DeviceTicket"
                                               << "FVE"
                                               << "fieldset"
                                               << "dropdownCaret"
                                               << "ariaLblCountry"
                                               << "easiSwitch"
                                               << "CTKGLIg"
                                               << "associate"
                                               << "Tfmuw"
                                               << "MembernamePasswordProfile"
                                               << "MembernameEn"
                                               << "lblNewPwd"
                                               << "WMUDW"
                                               << "lblVerification"
                                               << "hipDesc"
                                               << "LAUC"
                                               << "Whoops"
                                               << "fmicrosoft"
                                               << "prefetchPlt"
                                               << "phantom"
                                               << "gk2_exposure";

static QStringList fakeValueList = QStringList() << "ThermalHAL-UTIL"
                                                 << "ActivityManager"
                                                 << "[07_05_01_35_30530]"
                                                 << "getTaskSnapshot"
                                                 << "ActivityRecordf9f2944"
                                                 << "19690comgoogleandroidinputmethodlatintrainu0a79"
                                                 << "comgoogleandroidgmsautofillserviceAutofillService"
                                                 << "androidappIntentReceiverLeaked"
                                                 << "androidappLoadedApk$ReceiverDispatcher<init>LoadedApkjava1429"
                                                 << "androidappLoadedApkgetReceiverDispatcherLoadedApkjava1210"
                                                 << "androidappContextImplregisterReceiverInternalContextImpljava1476"
                                                 << "androidappContextImplregisterReceiverContextImpljava1449"
                                                 << "androidappContextImplregisterReceiverContextImpljava1437"
                                                 << "androidcontentContextWrapperregisterReceiverContextWrapperjava623"
                                                 << "lje<init>comgoogleandroidgms@201515026@201515"
                                                 << "lht<init>comgoogleandroidgms@201515026@201515"
                                                 << "kwiacomgoogleandroidgms@201515026@201515"
                                                 << "cbazacomgoogleandroidgms@201515026@201515"
                                                 << "kwqacomgoogleandroidgms@201515026@201515"
                                                 << "100306-3067585863"
                                                 << "kutbcomgoogleandroidgms@201515026@201515"
                                                 << "ldzonFillRequestcomgoogleandroidgms@201515026@201515"
                                                 << "androidserviceautofill-$$Lambda$I0gCKFrBTO70VZfSZTq2fj-wyG8acceptUnknown"
                                                 << "comandroidinternalutilfunctionpooledPooledLambdaImpldoInvokePooledLambdaImpljava287"
                                                 << "comandroidinternalutilfunctionpooledPooledLambdaImplinvokePooledLambdaImpljava182"
                                                 << "comandroidinternalutilfunctionpooledOmniFunctionrunOmniFunctionjava77"
                                                 << "androidosHandlerhandleCallbackHandlerjava873"
                                                 << "androidosHandlerdispatchMessageHandlerjava99"
                                                 << "androidosLooperloopLooperjava193"
                                                 << "androidappActivityThreadmainActivityThreadjava6746"
                                                 << "javalangreflectMethodinvokeNative"
                                                 << "comandroidinternalosRuntimeInit$MethodAndArgsCallerrunRuntimeInitjava493"
                                                 << "comandroidinternalosZygoteInitmainZygoteInitjava858"
                                                 << "actandroidintentactionMAIN"
                                                 << "cat[androidintentcategoryLAUNCHER]"
                                                 << "xyzautofarmerapp"
                                                 << "xyzautofarmerappxyzautofarmerappMainActivity"
                                                 << "ProcessCpuTracker"
                                                 << "xyzautofarmerappMainActivity"
                                                 << "19534xyzautofarmerapp"
                                                 << "1205system_server"
                                                 << "641mediacodec"
                                                 << "1578comandroidsystemui"
                                                 << "1760comandroidphone"
                                                 << "1569comgoogleandroidinputmethodlatin"
                                                 << "465androidhardwaresensors@10-service"
                                                 << "1726dataservices"
                                                 << "2170comqualcommqtiservicessecureuisui_service"
                                                 << "19451kworkeru86"
                                                 << "1745comqualcommqtitelephonyservice"
                                                 << "2157comandroidse"
                                                 << "593mediaextractor"
                                                 << "19448kworkeru84"
                                                 << "2268comgoogleandroidgmspersistent"
                                                 << "273mmc-cmdqd0"
                                                 << "357hwservicemanager"
                                                 << "427adsp_IPCRTR"
                                                 << "460androidhardwaregraphicscomposer@21-service"
                                                 << "490surfaceflinger"
                                                 << "11862kworkeru82"
                                                 << "31926kworker05"
                                                 << "450androidhardwareaudio@20-service"
                                                 << "487audioserver"
                                                 << "608mediametrics"
                                                 << "640androidhardwarecameraprovider@24-service"
                                                 << "2393comgoogleandroidgms"
                                                 << "9411comandroidsettings"
                                                 << "15319comfacebookkatani"
                                                 << "15473comfacebookkatani_43472e33-1a1c-69c1-aece-1488c79a8af3txt"
                                                 << "18851comgoogleandroidyoutube"
                                                 << "19534autofarmerapp"
                                                 << "ProcessRecordb1da96c"
                                                 << "actandroidintentactionDROPBOX_ENTRY_ADDED"
                                                 << "comgoogleandroidgmschimeraGmsIntentOperationService$PersistentTrustedReceiver"
                                                 << "Type0avg38612614min37307003max40602"
                                                 << "[07_05_01_36_00533]"
                                                 << "[07_05_01_36_30537]"
                                                 << "[07_05_01_37_00541]"
                                                 << "[07_05_01_37_30545]"
                                                 << "[07_05_01_38_00547]"
                                                 << "[07_05_01_38_30550]"
                                                 << "[07_05_01_39_00553]"
                                                 << "[07_05_01_39_30556]"
                                                 << "[07_05_01_40_00559]"
                                                 << "UsageStatsService"
                                                 << "[07_05_01_40_30562]"
                                                 << "[07_05_01_41_00567]"
                                                 << "[07_05_01_41_30570]"
                                                 << "[07_05_01_42_00573]"
                                                 << "eventTime81759161"
                                                 << "PowerManagerService"
                                                 << "DisplayPowerController"
                                                 << "KernelCpuSpeedReader"
                                                 << "KernelUidCpuTimeReader"
                                                 << "DisplayManagerService"
                                                 << "PowerManagerServiceDisplay"
                                                 << "DreamManagerService"
                                                 << "DreamController"
                                                 << "tagDreamManagerService"
                                                 << "PowerManagerServiceBroadcasts"
                                                 << "KeyguardStatusView"
                                                 << "KeyguardDisplayManager"
                                                 << "ActivityRecord326bf9"
                                                 << "[07_05_01_42_30576]"
                                                 << "[07_05_01_43_00579]"
                                                 << "ConnectivityService"
                                                 << "INTERNET&NOT_RESTRICTED&TRUSTED"
                                                 << "[07_05_01_43_30582]"
                                                 << "[07_05_01_44_00585]"
                                                 << "[07_05_01_44_30588]"
                                                 << "[07_05_01_45_00591]"
                                                 << "comgoogleandroidgmsstatsserviceDropBoxEntryAddedReceiver"
                                                 << "[07_05_01_45_30594]"
                                                 << "[07_05_01_46_00597]"
                                                 << "[07_05_01_46_30600]"
                                                 << "[07_05_01_47_00603]"
                                                 << "[07_05_01_47_30606]"
                                                 << "[07_05_01_48_00609]"
                                                 << "[07_05_01_48_30612]"
                                                 << "[07_05_01_49_00615]"
                                                 << "[07_05_01_49_30618]"
                                                 << "[07_05_01_50_00621]"
                                                 << "[07_05_01_50_30624]"
                                                 << "[07_05_01_51_00627]"
                                                 << "Type0avg36651897min34141003max39285004"
                                                 << "[07_05_01_51_30630]"
                                                 << "[07_05_01_52_00633]"
                                                 << "[07_05_01_52_30636]"
                                                 << "[07_05_01_53_00639]"
                                                 << "[07_05_01_53_30642]"
                                                 << "[07_05_01_54_00645]"
                                                 << "[07_05_01_54_30648]"
                                                 << "[07_05_01_55_00651]"
                                                 << "[07_05_01_55_30654]"
                                                 << "[07_05_01_56_00657]"
                                                 << "[07_05_01_56_30660]"
                                                 << "[07_05_01_57_00663]"
                                                 << "24376comgoogleandroidgmssnetu0a15"
                                                 << "24415comgoogleandroidmusicmainu0a62"
                                                 << "24428comvinsmartcontactsu0a16"
                                                 << "comgoogleandroidappsphotos"
                                                 << "ProcessRecorddf324a1"
                                                 << "NotificationService"
                                                 << "6484comandroidproviderscalendaru0a13"
                                                 << "[07_05_01_57_30666]"
                                                 << "[07_05_01_58_00670]"
                                                 << "[07_05_01_58_30673]"
                                                 << "[07_05_01_59_00675]"
                                                 << "BatteryExternalStatsWorker"
                                                 << "sysdevicessystemcpucpu0cpufreqstatstime_in_state"
                                                 << "[07_05_01_59_30678]"
                                                 << "[07_05_02_00_00681]"
                                                 << "[07_05_02_00_30684]"
                                                 << "[07_05_02_01_00687]"
                                                 << "[07_05_02_01_30690]"
                                                 << "[07_05_02_02_00693]"
                                                 << "[07_05_02_02_30696]"
                                                 << "[07_05_02_03_00699]"
                                                 << "[07_05_02_03_30702]"
                                                 << "[07_05_02_04_00705]"
                                                 << "[07_05_02_04_30708]"
                                                 << "[07_05_02_05_00711]"
                                                 << "[07_05_02_05_30715]"
                                                 << "uidpid1008511774"
                                                 << "uidpid1008111799"
                                                 << "[07_05_02_06_00718]"
                                                 << "[07_05_02_06_30721]"
                                                 << "Type0avg33470116min3308max34141003"
                                                 << "[07_05_02_07_00724]"
                                                 << "[07_05_02_07_30727]"
                                                 << "[07_05_02_08_00730]"
                                                 << "[07_05_02_08_30733]"
                                                 << "[07_05_02_09_00736]"
                                                 << "[07_05_02_09_30739]"
                                                 << "[07_05_02_10_00742]"
                                                 << "[07_05_02_10_30745]"
                                                 << "[07_05_02_11_00748]"
                                                 << "[07_05_02_11_30751]"
                                                 << "[07_05_02_12_00754]"
                                                 << "[07_05_02_12_30757]"
                                                 << "[07_05_02_13_00760]"
                                                 << "[07_05_02_13_30763]"
                                                 << "[07_05_02_14_00766]"
                                                 << "[07_05_02_14_30769]"
                                                 << "[07_05_02_15_00772]"
                                                 << "[07_05_02_15_30775]"
                                                 << "[07_05_02_16_00778]"
                                                 << "[07_05_02_16_30781]"
                                                 << "[07_05_02_17_00784]"
                                                 << "[07_05_02_17_30787]"
                                                 << "[07_05_02_18_00790]"
                                                 << "[07_05_02_18_30793]"
                                                 << "[07_05_02_19_00796]"
                                                 << "[07_05_02_19_30799]"
                                                 << "[07_05_02_20_00802]"
                                                 << "[07_05_02_20_30805]"
                                                 << "[07_05_02_21_00808]"
                                                 << "[07_05_02_21_30811]"
                                                 << "[07_05_02_22_00814]"
                                                 << "[07_05_02_22_30817]"
                                                 << "Type0avg33133076min33030003max33383003"
                                                 << "[07_05_02_23_00820]"
                                                 << "[07_05_02_23_30823]"
                                                 << "[07_05_02_24_00826]"
                                                 << "[07_05_02_24_30829]"
                                                 << "[07_05_02_25_00832]"
                                                 << "[07_05_02_25_30835]"
                                                 << "[07_05_02_26_00838]"
                                                 << "[07_05_02_26_30841]"
                                                 << "[07_05_02_27_00844]"
                                                 << "[07_05_02_27_30847]"
                                                 << "[07_05_02_28_00850]"
                                                 << "[07_05_02_28_30853]"
                                                 << "[07_05_02_29_00856]"
                                                 << "[07_05_02_29_30859]"
                                                 << "[07_05_02_30_00862]"
                                                 << "[07_05_02_30_30865]"
                                                 << "31768comfacebookkatanku0a139"
                                                 << "actcomfacebookmessagingipcpeersPROD"
                                                 << "comfacebookkatank"
                                                 << "[07_05_02_31_00868]"
                                                 << "actcomfacebookprofiloMAIN_PROCESS_STARTED_V4"
                                                 << "6547comandroidchromeu0a61"
                                                 << "NetworkRequestInfo"
                                                 << "binderDiedNetworkRequest"
                                                 << "androidosBinderProxy@b198850"
                                                 << "comgoogleandroidappsmessaging"
                                                 << "comfacebookpermissionprodFB_APP_COMMUNICATION"
                                                 << "BroadcastFilteree52623"
                                                 << "cmpcomfacebookkatankcomfacebookmqttliteMqttService"
                                                 << "hcomandroidservernotificationNotificationManagerService$WorkerHandler"
                                                 << "actX2KCNETWORKING_ACTIVE"
                                                 << "BroadcastFilter5f64bf1"
                                                 << "ReceiverList2cd352"
                                                 << "actandroidnetconnCONNECTIVITY_CHANGE"
                                                 << "actandroidnetconnINET_CONDITION_ACTION"
                                                 << "BroadcastFilter48baa36"
                                                 << "undrawn[Window879930d"
                                                 << "actmessenger_diode_badge_sync_action"
                                                 << "BroadcastFilterc8f6628"
                                                 << "BroadcastFilter15ed4db"
                                                 << "ReceiverList6b9ac4b"
                                                 << "ReceiverListd82d798"
                                                 << "comfacebookkatank10139u0"
                                                 << "actX2KCNETWORKING_INACTIVE"
                                                 << "BroadcastFilter7b11172"
                                                 << "ReceiverList89a9ea"
                                                 << "remote114791a"
                                                 << "comfacebookkatani10138u0"
                                                 << "remote9d73d7b"
                                                 << "remote6654bdd"
                                                 << "remote7db7dd5"
                                                 << "[07_05_02_31_30871]"
                                                 << "[07_05_02_32_00874]"
                                                 << "[07_05_02_32_30877]"
                                                 << "[07_05_02_33_00879]"
                                                 << "[07_05_02_33_30882]"
                                                 << "[07_05_02_34_00885]"
                                                 << "[07_05_02_34_30888]"
                                                 << "[07_05_02_35_00891]"
                                                 << "[07_05_02_35_30894]"
                                                 << "[07_05_02_36_00897]"
                                                 << "[07_05_02_36_30900]"
                                                 << "[07_05_02_37_00903]"
                                                 << "[07_05_02_37_30906]"
                                                 << "[07_05_02_38_00909]"
                                                 << "Type0avg33585625min33383003max34595"
                                                 << "[07_05_02_38_30912]"
                                                 << "[07_05_02_39_00915]"
                                                 << "[07_05_02_39_30918]"
                                                 << "[07_05_02_40_00921]"
                                                 << "[07_05_02_40_30924]"
                                                 << "[07_05_02_41_00927]"
                                                 << "[07_05_02_41_30930]"
                                                 << "[07_05_02_42_00933]"
                                                 << "[07_05_02_42_30936]"
                                                 << "3239comandroidproviderscalendaru0a13"
                                                 << "[07_05_02_43_00940]"
                                                 << "[07_05_02_43_30943]"
                                                 << "[07_05_02_44_00946]"
                                                 << "[07_05_02_44_30949]"
                                                 << "[07_05_02_45_00952]"
                                                 << "[07_05_02_45_30955]"
                                                 << "[07_05_02_46_00958]"
                                                 << "[07_05_02_46_30961]"
                                                 << "[07_05_02_47_00964]"
                                                 << "[07_05_02_47_30967]"
                                                 << "[07_05_02_48_00970]"
                                                 << "[07_05_02_48_30973]"
                                                 << "[07_05_02_49_00976]"
                                                 << "[07_05_02_49_30979]"
                                                 << "[07_05_02_50_00982]"
                                                 << "[07_05_02_50_30986]"
                                                 << "[07_05_02_51_00989]"
                                                 << "[07_05_02_51_30992]"
                                                 << "[07_05_02_52_00995]"
                                                 << "[07_05_02_52_30998]"
                                                 << "[07_05_02_53_01001]"
                                                 << "[07_05_02_53_31004]"
                                                 << "Type0avg33770664min33686max33838"
                                                 << "[07_05_02_54_01007]"
                                                 << "[07_05_02_54_31010]"
                                                 << "[07_05_02_55_01013]"
                                                 << "5896comgoogleandroidappstachyonu0a76"
                                                 << "5901comgoogleandroidappsmessagingu0a81"
                                                 << "cmpcomgoogleandroidappsmessagingshareddatamodelactionexecutionActionExecutorImpl$EmptyService"
                                                 << "uidpid100765896"
                                                 << "6026comandroidchromeu0a61"
                                                 << "9411comandroidsettings1000"
                                                 << "uidpid100815901";


AppMain::AppMain(QObject *parent) : QObject(parent)
{

}

void AppMain::handleRequest()
{
    QtCGI::Instance(true);
    QtCGI::Instance()->SetContentType(QtCGI::ContentTypeJSON);
    QJsonObject response,mainObject;
    if(QtCGI::Instance()->GetRequestMethod() == QtCGI::MethodPost) {
        mainObject["success"] = false;

        QString postData = QtCGI::Instance()->GetPostData();
        QMap<QString, QString> params = QtCGI::Instance()->GetQueryData();
        QString api = params.value("api");
        QString token = params.value("token");

        LOGD << "api: " << api;
        LOGD << "token: " << token;


        if(token.isEmpty() || api.isEmpty()) {
            mainObject["cgi_message"] = QString("Token(%1) or API(%2) is invalid)").arg(token).arg(api);
        } else {
            QJsonDocument postDoc = QJsonDocument::fromJson(postData.toUtf8());
            if(!postDoc.isNull() && postDoc.isObject()) {
                QJsonObject postObj = postDoc.object();

                if(postObj.contains("data") && postObj.contains("client_timestamp")) {
                    QString client_timestamp = postDoc["client_timestamp"].toString();
                    client_timestamp = decryptTimestamp(client_timestamp,token);

                    QString enc_data = postObj["data"].toString();

                    QString dec_data;
                    QEncryption::decrypt(enc_data,dec_data,getKeyFromTimestamp(client_timestamp),getIvFromTimestamp(client_timestamp));

                    // Encode password && secretkey
                    QJsonDocument requestJsonDoc = QJsonDocument::fromJson(dec_data.toUtf8());
                    QString action;
                    if(requestJsonDoc.isObject()) {
                        QJsonObject requestJsonObj = requestJsonDoc.object();

                        if(requestJsonObj.contains("action")) {
                            // Get action type
                            action = requestJsonObj.value("action").toString();
                            LOGD << "action: " << action;
                        }

                        if(action == "UpdatePassword" || action == "UpdateSecretkey") {
                            if(requestJsonObj.contains("clone_info")) {
                                QString base64Data = requestJsonObj.value("clone_info").toString();
                                QString rawData = QString::fromUtf8(QByteArray::fromBase64(base64Data.toUtf8()));
                                QJsonObject cloneInfo = QJsonDocument::fromJson(rawData.toUtf8()).object();
                                if(cloneInfo.contains("cz")) {
                                    bool cz = cloneInfo.value("cz").toBool();
                                    if(!cz) {
                                        // Encode password && secretkey from CGI
                                        encryptCloneInfo(cloneInfo,token);
                                        rawData = QString(QJsonDocument(cloneInfo).toJson());
                                        base64Data = rawData.toUtf8().toBase64();
                                        requestJsonObj["clone_info"] =  base64Data;
                                        dec_data =  QString(QJsonDocument(requestJsonObj).toJson());
                                    }
                                }
                            }
                        }
                    }


                    // Forward request
                    QString errorMsg, responBody;
                    int responseCode;
                    forwardRequest(api,dec_data,responBody,errorMsg,responseCode);

                    // Decode password && secretkey
                    if(action == "GetClone" || action == "GetCloneInfo") {
                        QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responBody.toUtf8());
                        if(responseJsonDoc.isObject()) {
                            QJsonObject responseJsonObj = responseJsonDoc.object();
                            QString base64Data = responseJsonObj.value("data").toString();
                            QString rawData = QString::fromUtf8(QByteArray::fromBase64(base64Data.toUtf8()));
                            QJsonObject cloneInfo = QJsonDocument::fromJson(rawData.toUtf8()).object();
                            if(cloneInfo.contains("mz") && cloneInfo.contains("cz")) {
                                bool mz = cloneInfo.value("mz").toBool();
                                bool cz = cloneInfo.value("cz").toBool();
                                if(!(mz || cz)) {
                                    // Decode password && secretkey from DB
                                    QString password = cloneInfo.value("password").toString();
                                    QString secretkey = cloneInfo.value("secretkey").toString();
                                    QString key = QEncryption::md5(token).toLower();
                                    QString iv = "congaubeoooooo@@";
                                    QEncryption::decrypt(password,password,key,iv,"Hex");
                                    QEncryption::decrypt(secretkey,secretkey,key,iv,"Hex");
                                    cloneInfo["password"] = password;
                                    cloneInfo["secretkey"] = secretkey;
                                } else if(cz) {
                                    // Decode password && secretkey from CGI
                                    decryptCloneInfo(cloneInfo,token);
                                }
                            }
                            rawData = QString(QJsonDocument(cloneInfo).toJson());
                            base64Data = rawData.toUtf8().toBase64();
                            responseJsonObj["data"] =  base64Data;
                            mainObject["data"] =  QString(QJsonDocument(responseJsonObj).toJson());
                        } else {
                            mainObject["data"] = responBody;
                        }
                    } else {
                        mainObject["data"] = responBody;
                    }


                    mainObject["cgi_message"] = errorMsg;
                    mainObject["response_code"] = responseCode;
                    mainObject["success"] = responseCode == 0;
                }
            } else {
                mainObject["cgi_message"] = "Could not parse POST data: " + postData;
            }
        }

        // encrypt main object
        QString server_timestamp = getCurrentTime();
        QString mainObjStr, encMainObjStr;
        mainObjStr = QJsonDocument(mainObject).toJson(QJsonDocument::Compact);
        QEncryption::encrypt(mainObjStr,encMainObjStr,getKeyFromTimestamp(server_timestamp),getIvFromTimestamp(server_timestamp));
        response["data"] = encMainObjStr;

        // encrypt server timestamp
        response["server_timestamp"] = encryptTimestamp(server_timestamp,token);

        // add fake values
        addFakeData(response,fakeKeyList,fakeValueList,1);
    }

    // Set the content
    QtCGI::Instance()->SetContent(QJsonDocument(response).toJson(QJsonDocument::Compact));
    // Write the content
    QtCGI::Instance()->WriteResponse();
    // Return the application execution
}

void AppMain::forwardRequest(QString &api, QString &rquestBody, QString &resposeBody, QString &errorMsg, int& responseCode)
{
    CkHttpRequest req;
    CkHttp http;
    http.put_ConnectTimeout(30);
    http.put_ReadTimeout(30);
    http.SetRequestHeader("mobile-secret-key", QtCGI::Instance()->GetRequestHeader(QtCGI::HeaderMobileSecretkey).toLower().toUtf8().data());
    http.SetRequestHeader("Content-Type", "application/json");

    QString url = "https://api8.autofarmer.xyz/public-api/v1/mobiles/" + api;
    CkHttpResponse *resp = http.PostJson(url.toUtf8().data(), rquestBody.toUtf8().data());

    responseCode = http.get_ConnectFailReason();

    if (!http.get_LastMethodSuccess()) {
        LOGD << "Error: " << http.lastErrorText();
        errorMsg = http.lastErrorText();
    } else {
        LOGD << "bodyStr: " << resp->bodyStr();;
        resposeBody = resp->bodyStr();
    }
}

QString AppMain::getCurrentTime() {
    std::string output;
    time_t t;
    struct tm *tmp;
    t = time(nullptr);
    tmp = gmtime(&t);

    char buffer[20];
    snprintf(buffer,20,"%4d:%02d:%02d:%02d:%02d:%02d",(tmp->tm_year + 1900), (tmp->tm_mon + 1), tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
    return QString(buffer);
}


QString AppMain::encryptTimestamp(QString& timestamp, QString& token) {
    QString keyFromToken = QEncryption::hashKey(token,8);
    QString ivFromToken = QEncryption::hashIv(token,4);
    QString encTimestamp;
    QEncryption::encrypt(timestamp,encTimestamp, keyFromToken,ivFromToken);
    return encTimestamp;
}

QString AppMain::decryptTimestamp(QString& timestamp, QString& token) {
    QString keyFromToken = QEncryption::hashKey(token,8);
    QString ivFromToken = QEncryption::hashIv(token,4);
    QString decTimestamp;
    QEncryption::decrypt(timestamp,decTimestamp, keyFromToken,ivFromToken);
    return decTimestamp;
}

void AppMain::encryptCloneInfo(QJsonObject &cloneInfo, QString token)
{
    // Decode password && secretkey from CGI
    if(token.isEmpty()) {
        LOGD << "token is empty";
        return;
    }

    if(cloneInfo.contains("uid")) {
        QString uid = cloneInfo.value("uid").toString();
        QString password = cloneInfo.value("password").toString();
        QString secretkey = cloneInfo.value("secretkey").toString();
        QString key = QEncryption::md5(token + uid).toLower();
        QString iv = "Pdt1794@Pdt1794@";
        QEncryption::encrypt(password,password,key,iv,"Hex");
        QEncryption::encrypt(secretkey,secretkey,key,iv,"Hex");
        cloneInfo["password"] = password;
        cloneInfo["secretkey"] = secretkey;
        cloneInfo["cz"] = true;
        LOGD << "key: " << key << " --iv:" << iv << " -- cloneInfo: " << cloneInfo;
    }
}

void AppMain::decryptCloneInfo(QJsonObject &cloneInfo, QString token)
{
    // Decode password && secretkey from CGI
    if(token.isEmpty()) {
        LOGD << "token is empty";
        return;
    }

    if(cloneInfo.contains("uid")) {
        QString uid = cloneInfo.value("uid").toString();
        QString password = cloneInfo.value("password").toString();
        QString secretkey = cloneInfo.value("secretkey").toString();
        QString key = QEncryption::md5(token + uid).toLower();
        QString iv = "Pdt1794@Pdt1794@";
        QEncryption::decrypt(password,password,key,iv,"Hex");
        QEncryption::decrypt(secretkey,secretkey,key,iv,"Hex");
        cloneInfo["password"] = password;
        cloneInfo["secretkey"] = secretkey;
        cloneInfo["cz"] = false;
        LOGD << "key: " << key << " --iv:" << iv << " -- cloneInfo: " << cloneInfo;
    }
}

QString AppMain::getKeyFromTimestamp(const QString& timeStamp) {
    QString key = QString(KEY_PREFIX) + timeStamp + timeStamp;
    return key.left(32);
}

QString AppMain::getIvFromTimestamp(const QString& timeStamp) {
    Q_UNUSED(timeStamp);
    return QString("Congaubeo@123560");
}

void AppMain::addFakeData(QJsonObject &object, QStringList &keyList, QStringList &valueList, int fieldNumber) {
    srand(time(nullptr));
    if(keyList.length() == valueList.length() &&
            fieldNumber <= keyList.length()) {

        for (int i = 0; i < fieldNumber; i++) {
            int randIndex = i + rand() % (fieldNumber - i);
            QString key = keyList[randIndex];
            keyList[randIndex] = keyList[i];
            keyList[i] = key;

            randIndex = i + rand() % (fieldNumber - i);
            QString value = valueList[randIndex];
            valueList[randIndex] = valueList[i];
            valueList[i] = value;

            QString encKey = getKeyFromTimestamp(getCurrentTime());
            static QString tmpiv = "phongdeptrai_phongvandeptrai_01071994";
            QEncryption::encrypt(value, value, encKey, tmpiv.left(16));
            object[key] = value;
        }
    }
}
