printf("%ld\n", strtol("222", 0, x)); //base x to long
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
regmatch_t matches[1];
regcomp(&reg, pattern.c_str(), REG_EXTENDED|REG_ICASE);
if(regexec(&reg, str.c_str(), 1, matches, 0) == 0)
cout << "match" << endl;
regfree(&reg);
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
template <typename T>
string toString(T n) { ostringstream ss; ss << n; return ss.str(); }

template <typename T>
T toNum(const string &Text) { istringstream ss(Text); T result; return ss >> result ? result : 0; }
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
vector<int> v(3, 5); //init vector to {5, 5, 5}
int arr[] = {2, 3, 4};
vector<int> v(arr, arr+3); //init vector to array
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
int* it = lower_bound(arr, arr+N, searchValue/*optional: comparator (it must be the same comparator used to sort)*/)
if(it == arr+N) cout << "not found" << endl;
else cout << "found " << *it << " at index " << it-arr << endl;
lower_bound: finds first that does not compare less than val.
upper_bound: finds first that compares greater than val.
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
int arr[] = {1, 2, 3}
reverse(arr, arr+N); //reverses the array, arr = {3, 2, 1}
sort(arr+N, arr) //reverse sort
partial_sort(arr, arr+k, arr+N) //partially sorts the array time: klog(N)
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
struct Point
{
	double x, y;
	string id;
};

Point origin = {0, 0, "origin"};
Point points[3] = {{3.4, 2.1, "myPoint1"},
    {2.4, 7.2, "myPoint2"},
    {4.1, 8.1, "myPoint3"}};
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include <algorithm>
int arr[] = {0, 1, 2, 3, 4};
next_permutation(arr, arr+5); //0, 1, 2, 4, 3
next_permutation(arr, arr+5); //0, 1, 3, 2, 4
prev_permutation(...)
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include <map>
#include <set>
//check if it contains an item
myMap.count(item);
mySet.count(item);
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
//When sorting small structs, for example:
struct Team
{
	int goldMedals;
	int silverMedals;
	int bronzeMedals;
};
//sort by gold, then silver then bronze
//instead of defining a comparison function, another way is to:

typedef pair<int, pair<int, int> > Team;

Team teams[10];
teams[0] = make_pair(4, make_pair(2, 6));
...

sort(teams, teams + 10);
//drawback: all variables will be sorted ascending or descending
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include <iomanip>
cout << fixed << setprecision(3) << 23.2341 << endl; //23.234 //formats forever until changed
cout.setwidth(8); //only for the next cout
cout << 2355 << endl; //"2355" -> "    2355"
cout.fill("-"); //forever until changed again
cout << 2355 << endl; //"2355" -> "------2355"
cout.setwidth(10);
cout << left << 2355 << endl; //"2355" -> "2355------"
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
scanf:

%d -> base10 int | %d+
%o -> base8 int  | %d+
%x -> base16 int | %d+
%a -> base10 or base16 double | ex. 123, 34.24, 5464.324e+3, 53423E+2, 0x242.435, base16 if preceded by 0x
%c -> char or array of chars | ex. scanf("%c", &mychar) -> 'a', scanf("%4c", mycharptr) -> "asdf" (\0 not included)
%s -> string
matching: scanf("abc%d", &myint) with input: "ab34 ascz24 abc345" would store 345 in myint, use %% to match %
%*d means match an int but dont store it in a parameter
%3d means match an integer but read only the 3 first characters
%lld stores in a long long int %d matches int, more specifiers are:
%le long double
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
class comparator
{
	bool operator()(int a, int b)
	{
		return a < b;
	}
}
priority_queue<int, vector<int>, comparator> pq;
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
Bellman-Ford for solving system of inequalities of the type x_i - x_j <= c
create a node for every x
create a source node
create a zero weight edge from s to every other node
for every inequality x_i - x_j <= c, make an edge from i to j of weight c
run bellman ford starting at s
the value for x_i is d_i
if there was a negative weight cycle, the system is inconsistent
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
max_element(arr, arr+N); //returns a pointer to the element
min_element(arr, arr+N);

//arrays must be sorted, can be used with set and map
merge() //same as set union but allows duplicates
set_union()//A + B
set_intersection()//A intersection B
set_difference()// A - B
set_symmetric_difference() // A^B
parameters: (begin1, end1, begin2, end2, begin_result); //returns a pointer to the end of the result, and the result is stored [begin_result to end_result)

accumulate(arr, arr+N, (long long)0); //add all elements by default, function can be specified, 0 is the initial value
double product = accumulate(all(v), double(1), multiplies<double>());
//plus, minus, divides, modulus, negate, equal_to, custom functions implemented same way as priority queue comparator
inner_product(all(v1), v2.begin(), 0); //scalar product [a, b, c].[d, e, f] = a*d + b*e + c*f
for_each(vec.begin(), vec.end(), func); //calls func(i) for every element in [begin, end)
nth_element (vec.begin(), vec.begin()+n, vec.end(), myfunction);
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
#include <ctype.h>
isalpha(char c), isupper(char c) ,islower(char c), isdigit(char c), ispunct(char c), toupper(char c), tolower(char c)
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
In a bipartite graph, the size of the maximum independent set (or dominating set) = V-MCBM
In a bipartite graph, the size of the min vertex cover = MCBM
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
char str[] = "abc. sdfksm sgfda afdex.. NJK- ,,   .  hb564567....";
char * token = strtok(str, ". ");
while (token != NULL)
{
    printf ("%s\n",token);
    token = strtok (NULL, ". ");
}
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
There are n^(n-2) spanning trees in a complete graph with n vertices
A dearangement is a permutation of a set where all elements are in a different position than their original position
der(n) = (n-1)*(der(n-1)+der(n-2)), der(0) = 1, der(1) = 0
a finite sequence of natural numbers can be a degree sequence of a graph iff the sum is even and sum from i=1 to k of d_i < k*(k-1) for 1<=k<=n
E - V - 2 = F where F is the number of faces in a planar graph
The number of pieces in which a circle is divided if n points on its circumference are joined by chords with no three internally concurrent:
g(n) = nCat4 + nCat2 + 1
A = i+b/2-1 where A is the area of a polygon, i is the number of integer points on the polygon and b is the number of integer points on the boundary
the number of spanning trees in complete a bipartite graph K(n, m) is m^(n-1) * n^(m-1)
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
//splitting by spaces
istringstream iss(line);
vector<string> tokens;
copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter<vector<string> >(tokens));
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
loop adjacent elements in a grid

//8 de alrededor
FOR(k, 0, 9)
if(k != 4) {
    ii next(i+k%2-1, j+k/3-1);
}

//arriba/abajo/der/izq: for(int k = 1; k < 9; k+=2)
FOR(k, 0, 4) {
	int k2 = k*2+1;
	ii next(i+k2%2-1, j+k2/3-1);
}
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
Primes less than 1000:
2     3     5     7    11    13    17    19    23    29    31    37
41    43    47    53    59    61    67    71    73    79    83    89
97   101   103   107   109   113   127   131   137   139   149   151
157   163   167   173   179   181   191   193   197   199   211   223
227   229   233   239   241   251   257   263   269   271   277   281
283   293   307   311   313   317   331   337   347   349   353   359
367   373   379   383   389   397   401   409   419   421   431   433
439   443   449   457   461   463   467   479   487   491   499   503
509   521   523   541   547   557   563   569   571   577   587   593
599   601   607   613   617   619   631   641   643   647   653   659
661   673   677   683   691   701   709   719   727   733   739   743
751   757   761   769   773   787   797   809   811   821   823   827
829   839   853   857   859   863   877   881   883   887   907   911
919   929   937   941   947   953   967   971   977   983   991   997
