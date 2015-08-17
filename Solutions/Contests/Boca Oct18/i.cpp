#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
#include <cstdlib>
#include <fstream>
#define INF 1000000000
#define FOR(i, a, b) for(int i=int(a); i<int(b); i++)
#define FORC(cont, it) for(typeof((cont).begin()) it=(cont).begin(); it!=(cont).end(); it++)
#define pb push_back
#define mp make_pair
using namespace std; typedef long long ll; typedef pair<ll, ll> ii; typedef vector<ll> vi; typedef vector<ii> vii; typedef vector<vi> vvi;

int intervalos[2190][2] = {{2184,2200},{27828,27846},{27829,27846},{27830,27846},{32214,32230},{57860,57876},{62244,62260},{87890,87906},{87890,87907},{87890,87908},{87890,87909},{87890,87910},{92274,92290},{110990,111010},{117920,117936},{122304,122320},{127374,127398},{147950,147966},{151058,151090},{151059,151090},{151060,151090},{151061,151090},{151062,151088},{151062,151089},{151062,151090},{152334,152350},{163488,163506},{171054,171072},{171054,171073},{171054,171074},{171054,171075},{171054,171076},{177980,177996},{182364,182380},{185924,185946},{185925,185946},{185926,185946},{208010,208026},{212394,212410},{238040,238056},{242424,242440},{249678,249696},{249678,249697},{249678,249698},{249678,249699},{249678,249700},{260810,260832},{260811,260832},{260812,260832},{260813,260832},{260814,260832},{264498,264520},{268070,268086},{272454,272470},{298100,298116},{302484,302500},{320870,320892},{320871,320892},{320872,320892},{323510,323532},{323510,323533},{323510,323534},{323510,323535},{323510,323536},{324564,324584},{324564,324585},{324564,324586},{328130,328146},{332514,332530},{339434,339456},{339434,339457},{339434,339458},{339434,339459},{339434,339460},{339435,339456},{339436,339456},{339437,339456},{339438,339456},{347004,347022},{358160,358176},{362544,362560},{388190,388206},{392574,392590},{399500,399520},{409188,409216},{409189,409216},{409190,409216},{418220,418236},{422600,422620},{422601,422620},{422602,422620},{422603,422620},{422604,422620},{448250,448266},{452634,452650},{471014,471040},{471015,471040},{471016,471040},{478280,478296},{482664,482680}
,{482664,482681},{482664,482682},{508310,508326},{512694,512710},{538338,538356},{538339,538356},{538340,538356},{542724,542740},{568370,568386},{572754,572770},{598400,598416},{598400,598417},{598400,598418},{598400,598419},{598400,598420},{602784,602800},{621500,621520},{628430,628446},{632814,632830},{658460,658476},{662844,662860},{673998,674016},{681564,681582},{681564,681583},{681564,681584},{681564,681585},{681564,681586},{681564,681587},{681564,681588},{688490,688506},{692874,692890},{696434,696456},{696435,696456},{696436,696456},{718520,718536},{722904,722920},{736554,736576},{748550,748566},{752934,752950},{760188,760206},{760188,760207},{760188,760208},{760188,760209},{760188,760210},{771320,771342},{771320,771343},{771320,771344},{771320,771345},{771320,771346},{771321,771342},{771321,771343},{771321,771344},{771321,771345},{771321,771346},{771322,771342},{771322,771343},{771322,771344},{771322,771345},{771322,771346},{771323,771342},{771323,771343},{771323,771344},{771323,771345},{771323,771346},{771324,771342},{771324,771343},{771324,771344},{771324,771345},{771324,771346},{778580,778596},{782964,782980},{797444,797470},{797445,797470},{797446,797470},{804384,804406},{808610,808626},{812994,813010},{820248,820268},{820248,820269},{820248,820270},{835074,835094},{835074,835095},{835074,835096},{838640,838656},{843024,843040},{849944,849966},{849945,849966},{849946,849966},{849947,849966},{849948,849966},{857514,857532},{868670,868686},{873054,873070},{891440,891462},{891440,891463},{891440,891464},{891440,891465},{891440,891466},{891441,891462},{891441,891463}
,{891441,891464},{891441,891465},{891441,891466},{891442,891462},{891442,891463},{891442,891464},{891442,891465},{891442,891466},{898700,898716},{903084,903100},{910010,910030},{928730,928746},{933104,933130},{933105,933130},{933106,933130},{933107,933130},{933108,933130},{933109,933130},{933110,933130},{933111,933130},{933112,933130},{933113,933130},{933114,933130},{958760,958776},{963144,963160},{972164,972192},{988790,988806},{993174,993190},{993174,993191},{993174,993192},{1018820,1018836},{1023204,1023220},{1041920,1041946},{1041920,1041947},{1041920,1041948},{1041921,1041946},{1041921,1041947},{1041921,1041948},{1041922,1041946},{1041922,1041947},{1041922,1041948},{1048848,1048866},{1048849,1048866},{1048850,1048866},{1053234,1053250},{1078880,1078896},{1083264,1083280},{1108910,1108926},{1108910,1108927},{1108910,1108928},{1108910,1108929},{1108910,1108930},{1113294,1113310},{1127474,1127498},{1127474,1127499},{1127474,1127500},{1132010,1132030},{1138940,1138956},{1143324,1143340},{1148394,1148418},{1168970,1168986},{1173354,1173370},{1184508,1184526},{1192074,1192092},{1192074,1192093},{1192074,1192094},{1192074,1192095},{1192074,1192096},{1199000,1199016},{1203384,1203400},{1206944,1206966},{1206945,1206966},{1206946,1206966},{1216224,1216248},{1216225,1216248},{1216226,1216248},{1216227,1216248},{1216228,1216248},{1225460,1225486},{1225461,1225486},{1225462,1225486},{1229030,1229046},{1233414,1233430},{1259060,1259076},{1263444,1263460},{1270698,1270716},{1270698,1270717},{1270698,1270718},{1270698,1270719},{1270698,1270720},{1278944,1278966},{1281830,1281852},{1281831,1281852},{1281832,1281852},{1281833,1281852},{1281834,1281852},{1289090,1289106},{1293474,1293490},{1319120,1319136},{1323504,1323520}
,{1330964,1330988},{1330964,1330989},{1330964,1330990},{1345584,1345604},{1345584,1345605},{1345584,1345606},{1349150,1349166},{1353534,1353550},{1360454,1360476},{1360455,1360476},{1360456,1360476},{1360457,1360476},{1360458,1360476},{1368024,1368042},{1379180,1379196},{1383564,1383580},{1390818,1390838},{1390818,1390839},{1390818,1390840},{1409210,1409226},{1413594,1413610},{1420520,1420540},{1439240,1439256},{1443620,1443640},{1443621,1443640},{1443622,1443640},{1443623,1443640},{1443624,1443640},{1462010,1462032},{1462011,1462032},{1462012,1462032},{1469270,1469286},{1473654,1473670},{1499300,1499316},{1503684,1503700},{1503684,1503701},{1503684,1503702},{1529330,1529346},{1533714,1533730},{1559358,1559376},{1559359,1559376},{1559360,1559376},{1563744,1563760},{1589390,1589406},{1593774,1593790},{1619420,1619436},{1619420,1619437},{1619420,1619438},{1619420,1619439},{1619420,1619440},{1623804,1623820},{1642520,1642540},{1649450,1649466},{1653834,1653850},{1679480,1679496},{1683864,1683880},{1695018,1695036},{1702584,1702602},{1702584,1702603},{1702584,1702604},{1702584,1702605},{1702584,1702606},{1709510,1709526},{1713894,1713910},{1717454,1717476},{1717455,1717476},{1717456,1717476},{1739540,1739556},{1743924,1743940},{1769570,1769586},{1773954,1773970},{1781208,1781226},{1781208,1781227},{1781208,1781228},{1781208,1781229},{1781208,1781230},{1781208,1781231},{1781208,1781232},{1792340,1792362},{1792341,1792362},{1792342,1792362},{1792343,1792362},{1792344,1792362},{1796030,1796054},{1796030,1796055},{1796030,1796056},{1796031,1796054},{1796031,1796055},{1796031,1796056},{1796032,1796054},{1796032,1796055},{1796032,1796056},{1799600,1799616},{1803984,1804000},{1829630,1829646},{1834014,1834030},{1856094,1856114},{1856094,1856115},{1856094,1856116},{1857020,1857046}
,{1859660,1859676},{1864044,1864060},{1870964,1870986},{1870964,1870987},{1870964,1870988},{1870964,1870989},{1870964,1870990},{1870965,1870986},{1870965,1870987},{1870965,1870988},{1870965,1870989},{1870965,1870990},{1870966,1870986},{1870966,1870987},{1870966,1870988},{1870966,1870989},{1870966,1870990},{1870967,1870986},{1870967,1870987},{1870967,1870988},{1870967,1870989},{1870967,1870990},{1870968,1870986},{1870968,1870987},{1870968,1870988},{1870968,1870989},{1870968,1870990},{1878534,1878552},{1889690,1889706},{1894074,1894090},{1919720,1919736},{1924104,1924120},{1931030,1931050},{1949750,1949766},{1954130,1954150},{1954131,1954150},{1954132,1954150},{1954133,1954150},{1954134,1954150},{1961388,1961408},{1961388,1961409},{1961388,1961410},{1979780,1979796},{1984164,1984180},{2009810,2009826},{2014194,2014210},{2014194,2014211},{2014194,2014212},{2032578,2032602},{2032579,2032602},{2032580,2032602},{2032581,2032602},{2032582,2032602},{2039840,2039856},{2044224,2044240},{2051390,2051416},{2069868,2069886},{2069869,2069886},{2069870,2069886},{2074254,2074270},{2099900,2099916},{2104284,2104300},{2129930,2129946},{2129930,2129947},{2129930,2129948},{2129930,2129949},{2129930,2129950},{2134314,2134330},{2153030,2153050},{2159960,2159976},{2164344,2164360},{2189990,2190006},{2194374,2194390},{2195828,2195856},{2195829,2195856},{2195830,2195856},{2205528,2205546},{2213094,2213112},{2213094,2213113},{2213094,2213114},{2213094,2213115},{2213094,2213116},{2220020,2220036},{2224404,2224420},{2227964,2227986},{2227964,2227987},{2227964,2227988},{2227964,2227989},{2227964,2227990},{2227965,2227986},{2227966,2227986},{2250050,2250066},{2254434,2254450},{2280080,2280096},{2284464,2284480},{2291718,2291736},{2291718,2291737},{2291718,2291738},{2291718,2291739},{2291718,2291740}
,{2302850,2302872},{2302851,2302872},{2302852,2302872},{2302853,2302872},{2302854,2302872},{2310110,2310126},{2314494,2314510},{2328980,2329002},{2328980,2329003},{2328980,2329004},{2328980,2329005},{2328980,2329006},{2328981,2329002},{2328982,2329002},{2335394,2335426},{2335395,2335426},{2335396,2335426},{2335397,2335426},{2335398,2335426},{2335399,2335426},{2335400,2335426},{2335401,2335426},{2335402,2335426},{2335403,2335426},{2335404,2335426},{2340140,2340156},{2344524,2344540},{2344844,2344866},{2344844,2344867},{2344844,2344868},{2344844,2344869},{2344844,2344870},{2366604,2366624},{2366604,2366625},{2366604,2366626},{2370170,2370186},{2374554,2374570},{2381474,2381496},{2381475,2381496},{2381476,2381496},{2381477,2381496},{2381478,2381496},{2389044,2389062},{2400200,2400216},{2404584,2404600},{2430230,2430246},{2434614,2434630},{2441540,2441560},{2460260,2460276},{2464640,2464660},{2464640,2464661},{2464640,2464662},{2464641,2464660},{2464641,2464661},{2464641,2464662},{2464642,2464660},{2464642,2464661},{2464642,2464662},{2464643,2464660},{2464644,2464660},{2490290,2490306},{2494674,2494690},{2520320,2520336},{2524704,2524720},{2524704,2524721},{2524704,2524722},{2531958,2531978},{2531958,2531979},{2531958,2531980},{2550350,2550366},{2554734,2554750},{2580378,2580396},{2580379,2580396},{2580380,2580396},{2584764,2584780},{2603150,2603172},{2603151,2603172},{2603152,2603172},{2610410,2610426},{2614794,2614810},{2640440,2640456},{2640440,2640457},{2640440,2640458},{2640440,2640459},{2640440,2640460},{2644824,2644840},{2663540,2663560},{2670470,2670486},{2674854,2674870},{2700500,2700516},{2704884,2704900},{2716038,2716056},{2723604,2723622},{2723604,2723623},{2723604,2723624},{2723604,2723625},{2723604,2723626},{2730530,2730546},{2734914,2734930},{2738474,2738496}
,{2738475,2738496},{2738476,2738496},{2742474,2742498},{2760230,2760256},{2760560,2760576},{2764944,2764960},{2790590,2790606},{2794974,2794990},{2802228,2802246},{2802228,2802247},{2802228,2802248},{2802228,2802249},{2802228,2802250},{2802228,2802251},{2802228,2802252},{2802228,2802253},{2802228,2802254},{2802228,2802255},{2802228,2802256},{2813360,2813382},{2813360,2813383},{2813360,2813384},{2813360,2813385},{2813360,2813386},{2813360,2813387},{2813360,2813388},{2813361,2813382},{2813362,2813382},{2813363,2813382},{2813364,2813382},{2820620,2820636},{2825004,2825020},{2850650,2850666},{2855034,2855050},{2877110,2877134},{2877110,2877135},{2877110,2877136},{2877111,2877134},{2877111,2877135},{2877111,2877136},{2877112,2877134},{2877112,2877135},{2877112,2877136},{2877113,2877134},{2877113,2877135},{2877113,2877136},{2877114,2877134},{2877114,2877135},{2877114,2877136},{2880680,2880696},{2885064,2885080},{2891984,2892006},{2891985,2892006},{2891986,2892006},{2891987,2892006},{2891988,2892006},{2899554,2899572},{2910710,2910726},{2915094,2915110},{2940740,2940756},{2945124,2945140},{2952044,2952068},{2952044,2952069},{2952044,2952070},{2952045,2952068},{2952045,2952069},{2952045,2952070},{2952046,2952068},{2952046,2952069},{2952046,2952070},{2952047,2952068},{2952047,2952069},{2952047,2952070},{2952048,2952068},{2952048,2952069},{2952048,2952070},{2952049,2952070},{2952050,2952070},{2970770,2970786},{2975150,2975170},{2975151,2975170},{2975152,2975170},{2975153,2975170},{2975154,2975170},{3000800,3000816},{3005184,3005200},{3030830,3030846},{3035214,3035230},{3035214,3035231},{3035214,3035232},{3060860,3060876},{3065244,3065260},{3090888,3090906},{3090889,3090906},{3090890,3090906},{3095274,3095290},{3102528,3102548},{3102528,3102549},{3102528,3102550},{3102528,3102551}
,{3102528,3102552},{3120920,3120936},{3125304,3125320},{3150950,3150966},{3150950,3150967},{3150950,3150968},{3150950,3150969},{3150950,3150970},{3155334,3155350},{3173720,3173742},{3173721,3173742},{3173722,3173742},{3174050,3174070},{3180980,3180996},{3185364,3185380},{3211010,3211026},{3215394,3215410},{3226548,3226566},{3234114,3234132},{3234114,3234133},{3234114,3234134},{3234114,3234135},{3234114,3234136},{3241040,3241056},{3245424,3245440},{3248984,3249006},{3248985,3249006},{3248986,3249006},{3271070,3271086},{3275454,3275470},{3301100,3301116},{3305484,3305500},{3312738,3312756},{3312738,3312757},{3312738,3312758},{3312738,3312759},{3312738,3312760},{3323870,3323892},{3323871,3323892},{3323872,3323892},{3323873,3323892},{3323874,3323892},{3331130,3331146},{3335514,3335530},{3361160,3361176},{3365544,3365560},{3387624,3387644},{3387624,3387645},{3387624,3387646},{3387624,3387647},{3387624,3387648},{3391190,3391206},{3395574,3395590},{3402494,3402516},{3402495,3402516},{3402496,3402516},{3402497,3402516},{3402498,3402516},{3410060,3410082},{3410061,3410082},{3410062,3410082},{3410063,3410082},{3410064,3410082},{3421220,3421236},{3425604,3425620},{3451250,3451266},{3455634,3455650},{3462560,3462580},{3469134,3469156},{3481280,3481296},{3485660,3485680},{3485661,3485680},{3485662,3485680},{3485663,3485680},{3485664,3485680},{3511310,3511326},{3515694,3515710},{3521210,3521232},{3541340,3541356},{3545720,3545742},{3545721,3545742},{3545722,3545742},{3545723,3545742},{3545724,3545740},{3545724,3545741},{3545724,3545742},{3571370,3571386},{3575754,3575770},{3601398,3601416},{3601399,3601416},{3601400,3601416},{3605784,3605800},{3611480,3611506},{3631430,3631446},{3635814,3635830},{3661460,3661476},{3661460,3661477},{3661460,3661478},{3661460,3661479},{3661460,3661480}
,{3665844,3665860},{3673098,3673118},{3673098,3673119},{3673098,3673120},{3684560,3684580},{3691490,3691506},{3695874,3695890},{3721520,3721536},{3725904,3725920},{3737058,3737076},{3744290,3744312},{3744291,3744312},{3744292,3744312},{3744624,3744642},{3744624,3744643},{3744624,3744644},{3744624,3744645},{3744624,3744646},{3751550,3751566},{3755934,3755950},{3759494,3759516},{3759495,3759516},{3759496,3759516},{3781580,3781596},{3785964,3785980},{3798680,3798708},{3811610,3811626},{3815994,3816010},{3823248,3823266},{3823248,3823267},{3823248,3823268},{3823248,3823269},{3823248,3823270},{3834380,3834402},{3834381,3834402},{3834382,3834402},{3834383,3834402},{3834384,3834402},{3841640,3841656},{3846024,3846040},{3871670,3871686},{3876054,3876070},{3898134,3898154},{3898134,3898155},{3898134,3898156},{3901700,3901716},{3906084,3906100},{3913004,3913026},{3913005,3913026},{3913006,3913026},{3913007,3913026},{3913008,3913026},{3920574,3920592},{3920574,3920593},{3920574,3920594},{3920574,3920595},{3920574,3920596},{3924464,3924488},{3924464,3924489},{3924464,3924490},{3924465,3924488},{3924465,3924489},{3924465,3924490},{3924466,3924488},{3924466,3924489},{3924466,3924490},{3931730,3931746},{3936114,3936130},{3959448,3959470},{3961760,3961776},{3966144,3966160},{3973070,3973090},{3991790,3991806},{3996170,3996190},{3996171,3996190},{3996172,3996190},{3996173,3996190},{3996174,3996190},{4021820,4021836},{4026204,4026220},{4044584,4044606},{4044584,4044607},{4044584,4044608},{4044584,4044609},{4044584,4044610},{4044585,4044606},{4044585,4044607},{4044585,4044608},{4044585,4044609},{4044585,4044610},{4044586,4044606},{4044586,4044607},{4044586,4044608},{4044586,4044609},{4044586,4044610},{4051850,4051866},{4056234,4056250},{4056234,4056251},{4056234,4056252},{4056234,4056253}
,{4056234,4056254},{4056234,4056255},{4056234,4056256},{4056234,4056257},{4056234,4056258},{4081880,4081896},{4086264,4086280},{4111908,4111926},{4111909,4111926},{4111910,4111926},{4116294,4116310},{4141940,4141956},{4146324,4146340},{4162938,4162960},{4162938,4162961},{4162938,4162962},{4162938,4162963},{4162938,4162964},{4162938,4162965},{4162938,4162966},{4171970,4171986},{4171970,4171987},{4171970,4171988},{4171970,4171989},{4171970,4171990},{4176354,4176370},{4195070,4195090},{4202000,4202016},{4206384,4206400},{4232030,4232046},{4236414,4236430},{4243668,4243688},{4243668,4243689},{4243668,4243690},{4247568,4247586},{4255134,4255152},{4255134,4255153},{4255134,4255154},{4255134,4255155},{4255134,4255156},{4262060,4262076},{4266444,4266460},{4270002,4270026},{4270003,4270026},{4270004,4270026},{4270005,4270026},{4270006,4270026},{4271054,4271080},{4292090,4292106},{4296474,4296490},{4301204,4301230},{4301204,4301231},{4301204,4301232},{4314860,4314882},{4314861,4314882},{4314862,4314882},{4322120,4322136},{4326504,4326520},{4333758,4333776},{4333758,4333777},{4333758,4333778},{4333758,4333779},{4333758,4333780},{4344890,4344912},{4344891,4344912},{4344892,4344912},{4344893,4344912},{4344894,4344912},{4352150,4352166},{4356534,4356550},{4382180,4382196},{4386564,4386580},{4408644,4408664},{4408644,4408665},{4408644,4408666},{4412210,4412226},{4416594,4416610},{4423514,4423536},{4423515,4423536},{4423516,4423536},{4423517,4423536},{4423518,4423536},{4431084,4431102},{4442240,4442256},{4446624,4446640},{4472270,4472286},{4476654,4476670},{4483580,4483600},{4483580,4483601},{4483580,4483602},{4502300,4502316},{4506680,4506700},{4506681,4506700},{4506682,4506700},{4506683,4506700},{4506684,4506700},{4532330,4532346},{4536714,4536730},{4562360,4562376},{4566744,4566760}
,{4566744,4566761},{4566744,4566762},{4592390,4592406},{4596774,4596790},{4622418,4622436},{4622419,4622436},{4622420,4622436},{4626804,4626820},{4652450,4652466},{4656834,4656850},{4682480,4682496},{4682480,4682497},{4682480,4682498},{4682480,4682499},{4682480,4682500},{4686864,4686880},{4695882,4695912},{4695883,4695912},{4695884,4695910},{4695884,4695911},{4695884,4695912},{4695885,4695910},{4695885,4695911},{4695885,4695912},{4695886,4695910},{4695886,4695911},{4695886,4695912},{4695887,4695912},{4695888,4695912},{4705580,4705600},{4712510,4712526},{4716894,4716910},{4742540,4742556},{4746924,4746940},{4758078,4758096},{4765644,4765662},{4765644,4765663},{4765644,4765664},{4765644,4765665},{4765644,4765666},{4772570,4772586},{4776954,4776970},{4780514,4780536},{4780515,4780536},{4780516,4780536},{4802600,4802616},{4806984,4807000},{4814238,4814258},{4814238,4814259},{4814238,4814260},{4831332,4831358},{4831332,4831359},{4831332,4831360},{4832630,4832646},{4837014,4837030},{4844268,4844286},{4844268,4844287},{4844268,4844288},{4844268,4844289},{4844268,4844290},{4855400,4855422},{4855401,4855422},{4855402,4855422},{4855403,4855422},{4855404,4855422},{4862660,4862676},{4867044,4867060},{4885430,4885452},{4885430,4885453},{4885430,4885454},{4885430,4885455},{4885430,4885456},{4885431,4885452},{4885432,4885452},{4892690,4892706},{4897074,4897090},{4919154,4919174},{4919154,4919175},{4919154,4919176},{4922720,4922736},{4927104,4927120},{4934024,4934046},{4934025,4934046},{4934026,4934046},{4934027,4934046},{4934028,4934046},{4941594,4941612},{4952750,4952766},{4957134,4957150},{4982780,4982796},{4987164,4987180},{4994090,4994110},{5003778,5003802},{5003778,5003803},{5003778,5003804},{5003778,5003805},{5003778,5003806},{5003779,5003804},{5003779,5003805},{5003779,5003806}
,{5003780,5003804},{5003780,5003805},{5003780,5003806},{5012810,5012826},{5017190,5017210},{5017191,5017210},{5017192,5017210},{5017193,5017210},{5017194,5017210},{5042840,5042856},{5047224,5047240},{5072870,5072886},{5077254,5077270},{5077254,5077271},{5077254,5077272},{5102900,5102916},{5107284,5107300},{5132928,5132946},{5132929,5132946},{5132930,5132946},{5137314,5137330},{5162960,5162976},{5167344,5167360},{5192990,5193006},{5192990,5193007},{5192990,5193008},{5192990,5193009},{5192990,5193010},{5197374,5197390},{5216088,5216110},{5216089,5216110},{5216090,5216110},{5223020,5223036},{5227404,5227420},{5253050,5253066},{5257434,5257450},{5268588,5268606},{5276154,5276172},{5276154,5276173},{5276154,5276174},{5276154,5276175},{5276154,5276176},{5276154,5276177},{5276154,5276178},{5283080,5283096},{5287464,5287480},{5291024,5291046},{5291025,5291046},{5291026,5291046},{5300304,5300328},{5313110,5313126},{5317494,5317510},{5343140,5343156},{5347524,5347540},{5354778,5354796},{5354778,5354797},{5354778,5354798},{5354778,5354799},{5354778,5354800},{5365910,5365932},{5365911,5365932},{5365912,5365932},{5365913,5365932},{5365914,5365932},{5373170,5373186},{5377554,5377570},{5384808,5384828},{5384808,5384829},{5384808,5384830},{5403200,5403216},{5407584,5407600},{5429664,5429684},{5429664,5429685},{5429664,5429686},{5429664,5429687},{5429664,5429688},{5433230,5433246},{5437614,5437630},{5444534,5444556},{5444535,5444556},{5444536,5444556},{5444537,5444556},{5444538,5444556},{5452104,5452122},{5456000,5456022},{5456001,5456022},{5456002,5456022},{5463260,5463276},{5467644,5467660},{5493290,5493306},{5497674,5497690},{5504600,5504620},{5523320,5523336},{5527700,5527720},{5527701,5527720},{5527702,5527720},{5527703,5527720},{5527704,5527720},{5536724,5536752},{5536725,5536752}
,{5536726,5536752},{5536727,5536752},{5536728,5536752},{5536729,5536752},{5536730,5536752},{5553350,5553366},{5557734,5557750},{5583380,5583396},{5587764,5587780},{5587764,5587781},{5587764,5587782},{5613410,5613426},{5617794,5617810},{5643434,5643456},{5643435,5643456},{5643436,5643456},{5643437,5643456},{5643438,5643456},{5643439,5643456},{5643440,5643456},{5647824,5647840},{5655078,5655102},{5655078,5655103},{5655078,5655104},{5655078,5655105},{5655078,5655106},{5655079,5655104},{5655079,5655105},{5655079,5655106},{5655080,5655104},{5655080,5655105},{5655080,5655106},{5655081,5655104},{5655081,5655105},{5655081,5655106},{5655082,5655104},{5655082,5655105},{5655082,5655106},{5655083,5655104},{5655083,5655105},{5655083,5655106},{5655084,5655104},{5655084,5655105},{5655084,5655106},{5673470,5673486},{5677854,5677870},{5703500,5703516},{5703500,5703517},{5703500,5703518},{5703500,5703519},{5703500,5703520},{5707884,5707900},{5726600,5726620},{5733530,5733546},{5737914,5737930},{5740220,5740242},{5763560,5763576},{5767944,5767960},{5775200,5775224},{5775200,5775225},{5775200,5775226},{5775201,5775224},{5775201,5775225},{5775201,5775226},{5775202,5775224},{5775202,5775225},{5775202,5775226},{5779094,5779116},{5779095,5779116},{5779096,5779116},{5779097,5779116},{5779098,5779116},{5786664,5786682},{5786664,5786683},{5786664,5786684},{5786664,5786685},{5786664,5786686},{5793590,5793606},{5797974,5797990},{5801534,5801556},{5801535,5801556},{5801536,5801556},{5823620,5823636},{5828004,5828020},{5853650,5853666},{5858034,5858050},{5865288,5865306},{5865288,5865307},{5865288,5865308},{5865288,5865309},{5865288,5865310},{5876420,5876442},{5876421,5876442},{5876422,5876442},{5876423,5876442},{5876424,5876442},{5883680,5883696},{5888064,5888080},{5913710,5913726},{5918094,5918110}
,{5940174,5940194},{5940174,5940195},{5940174,5940196},{5943740,5943756},{5948124,5948140},{5955044,5955066},{5955045,5955066},{5955046,5955066},{5955047,5955066},{5955048,5955066},{5955378,5955398},{5955378,5955399},{5955378,5955400},{5962614,5962632},{5973770,5973786},{5978154,5978170},{6003800,6003816},{6008184,6008200},{6015110,6015130},{6026570,6026592},{6026571,6026592},{6026572,6026592},{6033830,6033846},{6038210,6038230},{6038211,6038230},{6038212,6038230},{6038213,6038230},{6038214,6038230},{6063860,6063876},{6068244,6068260},{6086628,6086652},{6093890,6093906},{6098274,6098290},{6098274,6098291},{6098274,6098292},{6123920,6123936},{6128304,6128320},{6153948,6153966},{6153948,6153967},{6153948,6153968},{6153948,6153969},{6153948,6153970},{6153949,6153966},{6153950,6153966},{6158334,6158350},{6178458,6178480},{6183980,6183996},{6188364,6188380},{6214010,6214026},{6214010,6214027},{6214010,6214028},{6214010,6214029},{6214010,6214030},{6218394,6218410},{6230534,6230556},{6237110,6237130},{6244040,6244056},{6248424,6248440},{6250730,6250756},{6274070,6274086},{6278454,6278470},{6289608,6289626},{6289608,6289627},{6289608,6289628},{6289608,6289629},{6289608,6289630},{6297174,6297192},{6297174,6297193},{6297174,6297194},{6297174,6297195},{6297174,6297196},{6304100,6304116},{6308484,6308500},{6312044,6312066},{6312045,6312066},{6312046,6312066},{6334130,6334146},{6338514,6338530},{6345768,6345792},{6364160,6364176},{6368544,6368560},{6375798,6375816},{6375798,6375817},{6375798,6375818},{6375798,6375819},{6375798,6375820},{6386930,6386952},{6386931,6386952},{6386932,6386952},{6386933,6386952},{6386934,6386952},{6394190,6394206},{6398574,6398590},{6424220,6424236},{6428604,6428620},{6441402,6441426},{6450684,6450704},{6450684,6450705},{6450684,6450706},{6454250,6454266}
,{6458634,6458650},{6465552,6465576},{6465553,6465576},{6465554,6465576},{6465555,6465576},{6465556,6465576},{6465557,6465576},{6465558,6465576},{6473124,6473142},{6484280,6484296},{6488664,6488680},{6514310,6514326},{6518694,6518710},{6525620,6525640},{6525948,6525968},{6525948,6525969},{6525948,6525970},{6544340,6544356},{6548720,6548740},{6548721,6548740},{6548722,6548740},{6548723,6548740},{6548724,6548740},{6574370,6574386},{6578754,6578770},{6597138,6597162},{6597139,6597162},{6597140,6597162},{6597141,6597162},{6597142,6597162},{6604400,6604416},{6608784,6608800},{6608784,6608801},{6608784,6608802},{6634430,6634446},{6638814,6638830},{6664458,6664476},{6664459,6664476},{6664460,6664476},{6668844,6668860},{6694490,6694506},{6698874,6698890},{6724520,6724536},{6724520,6724537},{6724520,6724538},{6724520,6724539},{6724520,6724540},{6728904,6728920},{6741044,6741070},{6747620,6747640},{6747620,6747641},{6747620,6747642},{6747620,6747643},{6747620,6747644},{6747620,6747645},{6747620,6747646},{6747621,6747642},{6747621,6747643},{6747621,6747644},{6747621,6747645},{6747621,6747646},{6747622,6747642},{6747622,6747643},{6747622,6747644},{6747622,6747645},{6747622,6747646},{6754550,6754566},{6758934,6758950},{6777318,6777342},{6784580,6784596},{6788964,6788980},{6800118,6800136},{6807684,6807702},{6807684,6807703},{6807684,6807704},{6807684,6807705},{6807684,6807706},{6814610,6814626},{6818994,6819010},{6822554,6822576},{6822554,6822577},{6822554,6822578},{6822554,6822579},{6822554,6822580},{6822555,6822576},{6822555,6822577},{6822555,6822578},{6822555,6822579},{6822555,6822580},{6822556,6822576},{6822556,6822577},{6822556,6822578},{6822556,6822579},{6822556,6822580},{6844640,6844656},{6849024,6849040},{6874670,6874686},{6879054,6879070},{6886308,6886326},{6886308,6886327}
,{6886308,6886328},{6886308,6886329},{6886308,6886330},{6897440,6897462},{6897441,6897462},{6897442,6897462},{6897443,6897462},{6897444,6897462},{6904700,6904716},{6909084,6909100},{6934730,6934746},{6939114,6939130},{6961194,6961214},{6961194,6961215},{6961194,6961216},{6964760,6964776},{6969144,6969160},{6976064,6976086},{6976065,6976086},{6976066,6976086},{6976067,6976086},{6976068,6976086},{6983634,6983652},{6994790,6994806},{6999174,6999190},{7024820,7024836},{7029204,7029220},{7036130,7036150},{7054850,7054866},{7059230,7059250},{7059231,7059250},{7059232,7059250},{7059233,7059250},{7059234,7059250},{7084880,7084896},{7089264,7089280},{7096518,7096538},{7096518,7096539},{7096518,7096540},{7106718,7106750},{7106718,7106751},{7106718,7106752},{7106719,7106750},{7106719,7106751},{7106719,7106752},{7106720,7106748},{7106720,7106749},{7106720,7106750},{7106720,7106751},{7106720,7106752},{7106721,7106748},{7106721,7106749},{7106721,7106750},{7106721,7106751},{7106721,7106752},{7106722,7106748},{7106722,7106749},{7106722,7106750},{7106722,7106751},{7106722,7106752},{7114910,7114926},{7119294,7119310},{7119294,7119311},{7119294,7119312},{7144940,7144956},{7149324,7149340},{7167710,7167732},{7167711,7167732},{7167712,7167732},{7174968,7174986},{7174969,7174986},{7174970,7174986},{7179354,7179370},{7192122,7192146},{7205000,7205016},{7209384,7209400},{7235028,7235048},{7235028,7235049},{7235028,7235050},{7235029,7235048},{7235029,7235049},{7235029,7235050},{7235030,7235046},{7235030,7235047},{7235030,7235048},{7235030,7235049},{7235030,7235050},{7239414,7239430},{7258130,7258150},{7265060,7265076},{7269444,7269460},{7295090,7295106},{7299474,7299490},{7310628,7310646},{7318194,7318212},{7318194,7318213},{7318194,7318214},{7318194,7318215},{7318194,7318216},{7325120,7325136}
,{7329504,7329520},{7333064,7333086},{7333065,7333086},{7333066,7333086},{7354820,7354846},{7354821,7354846},{7354822,7354846},{7354823,7354846},{7354824,7354846},{7355150,7355166},{7359534,7359550},{7364264,7364286},{7364264,7364287},{7364264,7364288},{7364264,7364289},{7364264,7364290},{7364264,7364291},{7364264,7364292},{7370688,7370708},{7370688,7370709},{7370688,7370710},{7385180,7385196},{7389564,7389580},{7396818,7396836},{7396818,7396837},{7396818,7396838},{7396818,7396839},{7396818,7396840},{7407950,7407972},{7407951,7407972},{7407952,7407972},{7407953,7407972},{7407954,7407972},{7415210,7415226},{7419594,7419610},{7440498,7440526},{7440499,7440526},{7440500,7440526},{7445240,7445256},{7449624,7449640},{7470650,7470676},{7471704,7471724},{7471704,7471725},{7471704,7471726},{7475270,7475286},{7479654,7479670},{7486574,7486596},{7486575,7486596},{7486576,7486596},{7486577,7486596},{7486578,7486596},{7494144,7494162},{7503494,7503520},{7505300,7505316},{7509684,7509700},{7535330,7535346},{7539714,7539730},{7546640,7546660},{7565360,7565376},{7567742,7567782},{7567743,7567782},{7567744,7567782},{7567745,7567782},{7567746,7567782},{7567747,7567782},{7567748,7567782},{7567749,7567782},{7567750,7567782},{7567751,7567782},{7567752,7567782},{7567753,7567782},{7567754,7567782},{7569740,7569760},{7569741,7569760},{7569742,7569760},{7569743,7569760},{7569744,7569760},{7595390,7595406},{7599774,7599790},{7625420,7625436},{7629804,7629820},{7629804,7629821},{7629804,7629822},{7655450,7655466},{7659834,7659850},{7667088,7667108},{7667088,7667109},{7667088,7667110},{7685478,7685496},{7685479,7685496},{7685480,7685496},{7689864,7689880},{7715510,7715526},{7719894,7719910},{7738280,7738302},{7738281,7738302},{7738282,7738302},{7745540,7745556},{7745540,7745557},{7745540,7745558}
,{7745540,7745559},{7745540,7745560},{7749924,7749940},{7768640,7768660},{7775570,7775586},{7779954,7779970},{7805600,7805616},{7809984,7810000},{7821138,7821156},{7828700,7828722},{7828700,7828723},{7828700,7828724},{7828700,7828725},{7828700,7828726},{7828701,7828722},{7828701,7828723},{7828701,7828724},{7828701,7828725},{7828701,7828726},{7828702,7828722},{7828702,7828723},{7828702,7828724},{7828702,7828725},{7828702,7828726},{7828703,7828722},{7828703,7828723},{7828703,7828724},{7828703,7828725},{7828703,7828726},{7828704,7828722},{7828704,7828723},{7828704,7828724},{7828704,7828725},{7828704,7828726},{7835630,7835646},{7840014,7840030},{7843574,7843596},{7843575,7843596},{7843576,7843596},{7865660,7865676},{7870044,7870060},{7895690,7895706},{7900074,7900090},{7903634,7903658},{7903634,7903659},{7903634,7903660},{7903635,7903658},{7903635,7903659},{7903635,7903660},{7903636,7903658},{7903636,7903659},{7903636,7903660},{7907328,7907346},{7907328,7907347},{7907328,7907348},{7907328,7907349},{7907328,7907350},{7918458,7918482},{7918459,7918482},{7918460,7918482},{7918461,7918482},{7918462,7918482},{7918463,7918482},{7918464,7918482},{7925720,7925736},{7930104,7930120},{7955750,7955766},{7960134,7960150},{7982214,7982234},{7982214,7982235},{7982214,7982236},{7985780,7985796},{7990164,7990180},{7997084,7997106},{7997085,7997106},{7997086,7997106},{7997087,7997106},{7997088,7997106},{8004654,8004672},{8015810,8015826},{8020194,8020210},{8045840,8045856},{8050224,8050240},{8057150,8057170},{8075870,8075886},{8080250,8080270},{8080251,8080270},{8080252,8080270},{8080253,8080270},{8080254,8080270},{8105900,8105916},{8110284,8110300},{8135930,8135946},{8140314,8140330},{8140314,8140331},{8140314,8140332},{8165960,8165976},{8170344,8170360},{8195988,8196006},{8195989,8196006}
,{8195990,8196006},{8200374,8200390},{8226020,8226036},{8230404,8230420},{8237654,8237680},{8237655,8237680},{8237656,8237680},{8237657,8237680},{8237658,8237678},{8237658,8237679},{8237658,8237680},{8256050,8256066},{8256050,8256067},{8256050,8256068},{8256050,8256069},{8256050,8256070},{8260434,8260450},{8279150,8279170},{8286080,8286096},{8290464,8290480},{8308850,8308872},{8308851,8308872},{8308852,8308872},{8316110,8316126},{8320494,8320510},{8331648,8331666},{8339214,8339232},{8339214,8339233},{8339214,8339234},{8339214,8339235},{8339214,8339236},{8346140,8346156},{8350524,8350540},{8354082,8354106},{8354083,8354106},{8354084,8354106},{8354085,8354106},{8354086,8354106},{8368700,8368726},{8368701,8368726},{8368702,8368726},{8376170,8376186},{8380554,8380570},{8406200,8406216},{8410584,8410600},{8417838,8417856},{8417838,8417857},{8417838,8417858},{8417838,8417859},{8417838,8417860},{8420724,8420746},{8428970,8428992},{8428971,8428992},{8428972,8428992},{8428973,8428992},{8428974,8428992},{8436230,8436246},{8440614,8440630},{8466260,8466276},{8470644,8470660},{8483442,8483462},{8483442,8483463},{8483442,8483464},{8483442,8483465},{8483442,8483466},{8492724,8492744},{8492724,8492745},{8492724,8492746},{8496290,8496306},{8500674,8500690},{8505882,8505906},{8507594,8507616},{8507595,8507616},{8507596,8507616},{8507597,8507616},{8507598,8507616},{8515164,8515182},{8526320,8526336},{8530704,8530720},{8551272,8551296},{8556350,8556366},{8560734,8560750},{8567660,8567680},{8572190,8572216},{8572191,8572216},{8572192,8572216},{8586380,8586396},{8590760,8590780},{8590761,8590780},{8590762,8590780},{8590763,8590780},{8590764,8590780},{8616410,8616426},{8620794,8620810},{8646440,8646456},{8650824,8650840},{8650824,8650841},{8650824,8650842},{8676470,8676486},{8680854,8680870}
,{8706498,8706516},{8706499,8706516},{8706500,8706516},{8710884,8710900},{8736530,8736546},{8740914,8740930},{8766560,8766576},{8766560,8766577},{8766560,8766578},{8766560,8766579},{8766560,8766580},{8766560,8766581},{8766560,8766582},{8766560,8766583},{8766560,8766584},{8766560,8766585},{8766560,8766586},{8770944,8770960},{8789660,8789680},{8796590,8796606},{8800974,8800990},{8808224,8808248},{8808224,8808249},{8808224,8808250},{8808225,8808248},{8808225,8808249},{8808225,8808250},{8808226,8808248},{8808226,8808249},{8808226,8808250},{8808227,8808248},{8808227,8808249},{8808227,8808250},{8808228,8808248},{8808228,8808249},{8808228,8808250},{8826620,8826636},{8831004,8831020},{8842158,8842176},{8849724,8849742},{8849724,8849743},{8849724,8849744},{8849724,8849745},{8849724,8849746},{8856650,8856666},{8861034,8861050},{8864594,8864616},{8864595,8864616},{8864596,8864616},{8879420,8879442},{8879421,8879442},{8879422,8879442},{8886680,8886696},{8891064,8891080},{8895284,8895306},{8902214,8902246},{8902215,8902246},{8902216,8902246},{8902217,8902246},{8902218,8902242},{8902218,8902243},{8902218,8902244},{8902218,8902245},{8902218,8902246},{8902219,8902244},{8902219,8902245},{8902219,8902246},{8902220,8902244},{8902220,8902245},{8902220,8902246},{8916710,8916726},{8921094,8921110},{8928344,8928366},{8928344,8928367},{8928344,8928368},{8928344,8928369},{8928344,8928370},{8928345,8928366},{8928345,8928367},{8928345,8928368},{8928345,8928369},{8928345,8928370},{8928346,8928366},{8928346,8928367},{8928346,8928368},{8928346,8928369},{8928346,8928370},{8928347,8928366},{8928347,8928367},{8928347,8928368},{8928347,8928369},{8928347,8928370},{8928348,8928366},{8928348,8928367},{8928348,8928368},{8928348,8928369},{8928348,8928370},{8939478,8939502},{8939479,8939502},{8939480,8939502}
,{8939481,8939502},{8939482,8939502},{8939483,8939502},{8939484,8939502},{8946740,8946756},{8951124,8951140},{8963114,8963136},{8976770,8976786},{8981154,8981170},{8981474,8981500},{9003234,9003254},{9003234,9003255},{9003234,9003256},{9006800,9006816},{9011184,9011200},{9018102,9018126},{9018103,9018126},{9018104,9018126},{9018105,9018126},{9018106,9018126},{9018107,9018126},{9018108,9018126},{9025674,9025692},{9036830,9036846},{9041214,9041230},{9066860,9066876},{9071244,9071260},{9078170,9078190},{9096890,9096906},{9101270,9101290},{9101271,9101290},{9101272,9101290},{9101273,9101290},{9101274,9101290},{9126920,9126936},{9131304,9131320},{9156950,9156966},{9161334,9161350},{9161334,9161351},{9161334,9161352},{9182354,9182386},{9182355,9182386},{9182356,9182386},{9182357,9182386},{9182358,9182382},{9182358,9182383},{9182358,9182384},{9182358,9182385},{9182358,9182386},{9186980,9186996},{9191364,9191380},{9198620,9198644},{9198620,9198645},{9198620,9198646},{9217008,9217026},{9217009,9217026},{9217010,9217026},{9221394,9221410},{9247040,9247056},{9251424,9251440},{9277070,9277086},{9277070,9277087},{9277070,9277088},{9277070,9277089},{9277070,9277090},{9281454,9281470},{9300170,9300190},{9307100,9307116},{9311484,9311500},{9337130,9337146},{9341514,9341530},{9352668,9352686},{9360234,9360252},{9360234,9360253},{9360234,9360254},{9360234,9360255},{9360234,9360256},{9367160,9367176},{9371544,9371560},{9375104,9375126},{9375105,9375126},{9375106,9375126},{9376154,9376180},{9376155,9376180},{9376156,9376180},{9376157,9376180},{9376158,9376180},{9378798,9378818},{9378798,9378819},{9378798,9378820},{9397190,9397206},{9401574,9401590},{9427220,9427236},{9431604,9431620},{9435170,9435192},{9438858,9438876},{9438858,9438877},{9438858,9438878},{9438858,9438879},{9438858,9438880}
,{9449990,9450012},{9449991,9450012},{9449992,9450012},{9449993,9450012},{9449994,9450012},{9457250,9457266},{9461634,9461650},{9487280,9487296},{9491664,9491680},{9513740,9513766},{9513741,9513766},{9513742,9513766},{9513743,9513766},{9513744,9513764},{9513744,9513765},{9513744,9513766},{9517310,9517326},{9521694,9521710},{9528614,9528636},{9528615,9528636},{9528616,9528636},{9528617,9528636},{9528618,9528636},{9536184,9536202},{9547340,9547356},{9551724,9551740},{9577370,9577386},{9581754,9581770},{9588680,9588700},{9607400,9607416},{9611780,9611800},{9611781,9611800},{9611782,9611800},{9611783,9611800},{9611784,9611800},{9637430,9637446},{9641814,9641830},{9667460,9667476},{9671844,9671860},{9671844,9671861},{9671844,9671862},{9697490,9697506},{9701874,9701890},{9727518,9727536},{9727519,9727536},{9727520,9727536},{9731904,9731920},{9740462,9740500},{9757550,9757566},{9761934,9761950},{9787580,9787596},{9787580,9787597},{9787580,9787598},{9787580,9787599},{9787580,9787600},{9791964,9791980},{9810680,9810700},{9817610,9817626},{9821994,9822010},{9847640,9847656},{9852024,9852040},{9863178,9863196},{9870744,9870762},{9870744,9870763},{9870744,9870764},{9870744,9870765},{9870744,9870766},{9877670,9877686},{9882054,9882070},{9885614,9885636},{9885615,9885636},{9885616,9885636},{9907700,9907716},{9912084,9912100},{9937730,9937746},{9942114,9942130},{9949368,9949386},{9949368,9949387},{9949368,9949388},{9949368,9949389},{9949368,9949390},{9960500,9960522},{9960501,9960522},{9960502,9960522},{9960503,9960522},{9960504,9960522},{9964188,9964210},{9967760,9967776},{9972144,9972160},{9997790,9997806}};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int a, b, t = 0;
        cin >> a >> b;
        FOR(i, 0, 2190) {
            if(a <= intervalos[i][0] && intervalos[i][1] <= b) t++;
        }
        cout << t << endl;
    }
}