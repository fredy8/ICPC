template <typename T>
string toString(T n) { ostringstream ss; ss << n; return ss.str(); }

template <typename T>
T toNum(const string &Text) { istringstream ss(Text); T result; return ss >> result ? result : 0; }