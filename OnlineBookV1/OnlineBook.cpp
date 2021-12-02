#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<double> point;

#define scf                   scanf
#define prf                   printf
#define f_io                  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define file_r                freopen("input.txt", "r", stdin)
#define file_w                freopen("output.txt", "w", stdout)

#define all(c)                c.begin(), c.end()
#define sz(c)                 ((int)((c).size()))
//#define pb                    push_back
#define eb                    emplace_back

#define mkp                   make_pair
#define mkt                   make_tuple
#define xf                    first
#define ys                    second

#define getbit(i, mask)       ((mask & (((__typeof(mask))1)<<(i))) != 0)
#define setbit(i, mask)       (mask |= ((__typeof(mask))1)<<(i))
#define clrbit(i, mask)       (mask &= ~(((__typeof(mask))1)<<(i)))
#define togglebit(i, mask)    (mask ^= ((__typeof(mask))1)<<(i))

#define isodd(x)              ((x) & 1)
#define iseven(x)             (!((x) & 1))

#define lp(i, s, e)           for(auto i = s; i < e; ++i)
#define rlp(i, e, s)          for(auto i = e; i > s; --i)
#define lp_(var , c)          for(const auto &var : c)

#define mems(c,val)           memset(c, val, sizeof(c))

#define OOi                   (~(1<<31))
#define OOl                   (~(1LL<<63))

#define PI                    (3.14159265358979)
#define EPS                   (1e-9)

#define watch(x)              cerr << ">> " << (#x) << " = " << (x) << endl

inline int dcmp(double a, double b) {
	return fabs(a - b) < EPS ? 0 : a < b ? -1 : +1;
}
//____________________________________________________________________________.
namespace fs =  std::filesystem;

class FileManager{
public:
	static string gluePath(const string &first, const string &second){
		return first + "\\" + second;
	}

	static bool isExist(const string &path){
		return fs::exists(path);
	}

	static void createFile(const string &file_path, const vector<string> &lines = {}){
		ofstream f;

		f.open(file_path, ios::trunc);

		for(int i = 0; i < sz(lines); i++){
			if(i) f << "\n";
			f << lines[i];
		}
		f.close();
	}

	static void updateFile(const string &file_path, const vector<string> &lines, bool app){
		if(not app){
			createFile(file_path, lines);
			return ;
		}
		ofstream f;
		f.open(file_path, ios::app);
		for(const auto &line : lines) f << "\n" << line;
		f << "\n";
		f.close();
	}

	static vector<string> loadFile(const string &file_path){
		ifstream f;
		f.open(file_path);

		vector<string> lines;
		string buff;

		while(getline(f, buff)) lines.emplace_back(move(buff));

		f.close();
		return lines;
	}

	static vector<string> loadNamesWithoutExtension(const string &dir_path){
		vector<string> names;
	    for (const auto & entry : fs::directory_iterator(dir_path))
	    	names.eb(entry.path().stem().string());
	    return names;
	}

	static void removeFile(const string &file_path){
		fs::remove(file_path);
	}
};

class Utils{
public:
	template<class type>
	static auto str_to_vec(const string &str){
		istringstream iss {str};
		vector<type> ret;
		type x;
		while(iss >> x) ret.emplace_back(x);
		return ret;
	}

	static string getRnd(){
		static unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
		static default_random_engine generator(seed);
		static uniform_int_distribution<ll> distribution(1, 10000);
		return to_string(distribution(generator));
	}

	static string getDate(){
		 time_t tp = chrono::system_clock::to_time_t(chrono::system_clock::now());
		  string date =  ctime(&tp);
		  if(!date.empty() and date.back() == '\n') date.pop_back();
		  return date;
	}
};

class Book{
	inline static const string rootPath = "D:\\workspaces\\eclipse_ws\\OnlineBook\\DB\\Books";
	string id;
	string name;
	int page_cnt;
	string file_path;
	vector<string> pages;

	Book() {}

	vector<string> fileRep() const {
		vector<string> lines;
		lines.emplace_back(id);
		lines.emplace_back(name);
		lines.emplace_back(to_string(page_cnt));
		lines.emplace_back(file_path);
		for(const auto &page: pages) lines.emplace_back(page);
		return lines;
	}

	static Book loadBook(const string &id){
		assert(not id.empty());
		return Book(FileManager::loadFile(FileManager::gluePath(rootPath, id + ".txt")));
	}

	Book(const vector<string> &lines){
		tie(id, name, page_cnt, file_path) = mkt(lines[0], lines[1], stoi(lines[2]), lines[3]);
		pages = vector<string>(lines.begin()+4, lines.end());
	}

public:
	Book(const string &name, const vector<string> &pages){
		// create new book on disk
		id = Utils::getRnd();
		this->name = name;
		page_cnt = pages.size();
		this->file_path = FileManager::gluePath(rootPath, id + ".txt");
		this->pages = pages;
		FileManager::createFile(file_path, fileRep());
	}

	const string& page(int page_idx) const {
		assert(!isDead() and page_idx > -1 and page_idx < page_cnt);
		return pages[page_idx];
	}

	void remove(){
		assert(not isDead());
		FileManager::removeFile(file_path);
		id.clear();
	}

	bool isDead() const {
		return id.empty();
	}

	const string& getId() const {
		return id;
	}
	const string& getName() const {
		return name;
	}
	const int& getPageCnt() const{
		return page_cnt;
	}
	string getInfo() const {
		ostringstream oss;
		oss << "Book[" << id << "]" << ": " << name << ", " << "pages:" << page_cnt << " ." << "\n";
		return oss.str();
	}
	bool operator < (const Book &rhs) const {
		return this->id < rhs.id;
	}

	static map<string, Book> loadBooks(){
		map<string, Book> books;
		for(const string &id : FileManager::loadNamesWithoutExtension(rootPath))
			books.emplace(id, loadBook(id));
		return books;
	}
};

class User{
	inline static const string rootPath = "D:\\workspaces\\eclipse_ws\\OnlineBook\\DB\\Users";

	string uname; // unique => works as id
	string email;
	string password;
	string file_path;
	bool logged;

	vector<string> fileRep() const {
		vector<string> lines;
		lines.emplace_back(uname);
		lines.emplace_back(email);
		lines.emplace_back(password);
		lines.emplace_back(file_path);
		return lines;
	}

	User(const vector<string> &lines){
		tie(uname, email, password, file_path) = mkt(lines[0], lines[1], lines[2], lines[3]);
		logged = true;
	}

	bool verifyPassword(const string &otherPassword) const {
		return password == otherPassword;
	}

protected:
	User(): logged(false) {}

public:
	bool signUp(const string &username, const string &email, const string &password){
		if(FileManager::isExist(FileManager::gluePath(rootPath, username + ".txt"))) return false;
		this->uname = username;
		this->email = email;
		this->password = password;
		this->file_path = FileManager::gluePath(rootPath, uname + ".txt");
		this->logged = true;
		FileManager::createFile(file_path, fileRep());
		return 1;
	}

	bool login(const string &username, const string &password){
		// read profiles on disk, check if valid, load if ok
		if(not FileManager::isExist(FileManager::gluePath(rootPath, username + ".txt"))) return false;

		const User &profile = User(FileManager::loadFile(FileManager::gluePath(rootPath, username + ".txt")));

		if(!profile.verifyPassword(password)) return false;

		*this = move(profile);

		return true;
	}

	bool isLoggedIn() const {
		return logged;
	}

	const string& getUserName() const{
		assert(isLoggedIn());
		return uname;
	}

	string getInfo() const {
		assert(isLoggedIn());
		ostringstream oss;
		oss << "username: " << uname << ", email: " << email;
		return oss.str();
	}

	void logout(){
		uname.clear();
		email.clear();
		password.clear();
		file_path.clear();
		logged = false;
	}
};

class Admin : public User{
public:
	Admin() {}

	void addBook(const string &name, const vector<string> &pages, map<string, Book> &sys_books) const {
		// call Book constructor, add the created book to sysBooks
		const Book &book = Book(name, pages);
		string book_id = book.getId();
		sys_books.emplace(book_id, move(book));
	}
};

class Session{
	inline static const string rootPath = "D:\\workspaces\\eclipse_ws\\OnlineBook\\DB\\Sessions";

	string id;
	const Book &book;
	int idx_page;
	string last_view_date;
	string file_path;

	Session(const vector<string> &lines, const Book &book_ref): book(book_ref){
		tie(id, idx_page, last_view_date, file_path) = mkt(lines[0], stoi(lines[2]), lines[3], lines[4]);
	}

	vector<string> fileRep () const {
		vector<string> lines;
		lines.emplace_back(id);
		lines.emplace_back(book.getId());
		lines.emplace_back(to_string(idx_page));
		lines.emplace_back(last_view_date);
		lines.emplace_back(file_path);
		return lines;
	}

	static string linesPickBookId(const vector<string> &lines) {
		return lines[1];
	}

public:
	Session(const Book &book): book(book){
		id = Utils::getRnd();
		idx_page = 0;
		last_view_date = "Not viewed yet!";
		file_path = FileManager::gluePath(rootPath, id + ".txt");
		FileManager::createFile(file_path, fileRep());
	}

	static Session loadSession (const map<string, Book> &sys_books, const string &session_id){
		// load session from disk
		const vector<string> &lines = FileManager::loadFile(FileManager::gluePath(rootPath, session_id + ".txt"));
		const Book &book = sys_books.find(linesPickBookId(lines))->ys;
		return Session(lines, book);
	}

	const string& getId() const {
		return id;
	}

	string getInfo() const {
		ostringstream oss;
		oss << "Sess[" << id << "]: " << "\t";
		oss << "book[" << book.getName() << "]" << ", " << idx_page << "/" << book.getPageCnt() << ", " << "on " << last_view_date;
		return oss.str();
	}

	const string& open(){
		 // update last_view_date, return page view string
		last_view_date = Utils::getDate();
		return book.page(idx_page);
	}

	string nextPage(){
		 // update idx_page, return page view
		last_view_date = Utils::getDate();
		return book.page(++idx_page);
	}

	string prevPage(){
		// update idx_page, return page view
		last_view_date = Utils::getDate();
		return book.page(--idx_page);
	}

	string jmpToPage(int new_idx_page){
		// update idx_page, return page view
		last_view_date = Utils::getDate();
		return book.page(idx_page=new_idx_page);
	}

	void close(){
		last_view_date = Utils::getDate();
		FileManager::updateFile(file_path, fileRep(), false);
	}

	bool hasDeadBook(){
		// check if the book has disk base
		return book.isDead();
	}

	bool isDead() const {
		return id.empty();
	}

	void remove(){
		//remove Session file from disk, reset id to ""
		FileManager::removeFile(file_path);
		id = last_view_date = file_path = "";
	}

	bool operator < (const Session &rhs) const {
		return id < rhs.id;
	}
};

class Customer : public User{
	inline static const string rootPath = "D:\\workspaces\\eclipse_ws\\OnlineBook\\DB\\Customers";
	map<string, Session> sessions;
	string file_path;
public:
	Customer() {}

	bool signUp(const string &username, const string &email, const string &password){
		if(!User::signUp(username, email, password)) return 0;
		file_path = FileManager::gluePath(rootPath, getUserName() + ".txt");
		FileManager::createFile(file_path);
		return 1;
	}

	bool login(const string &username, const string &password, const map<string, Book> &sys_books){
		// profile login, then if success, load from disk my sessions using sysBooks, otherwise nothing.

		if(!User::login(username, password)) return 0;

		file_path = FileManager::gluePath(rootPath, getUserName() + ".txt");

		for(const string &sess_id : FileManager::loadFile(file_path))
			if(not sess_id.empty())
				sessions.emplace(sess_id, Session::loadSession(sys_books, sess_id));

		return 1;
	}

	void logout(){
		User::logout();
		sessions.clear();
		file_path.clear();
	}

	string createSession(const Book &book){
		const Session &sess = Session(book);
		FileManager::updateFile(file_path, {sess.getId()}, true);
		string sess_id = sess.getId();
		sessions.emplace(sess_id, move(sess));
		return sess_id;
	}

	void removeSession(const string &session_id){
		// calls Session remove, erase from sessions, update Customer file on disk to erase Session id
		auto it = sessions.find(session_id);
		assert(it != sessions.end());
		it->second.remove();
		vector<string> sess_ids= FileManager::loadFile(file_path);
		sess_ids.erase(find(all(sess_ids), session_id));
		FileManager::updateFile(file_path, move(sess_ids), false);
		sessions.erase(it);
	}

	vector<string> getSesstionsInfo() const {
		vector<string> lines;

		for(const auto &kv : sessions)
				lines.emplace_back(kv.ys.getInfo());

		return lines;
	}

	string openSession(const string &session_id){
		return sessions.find(session_id)->second.open();
	}

	string nextPage(const string &session_id){
		return sessions.find(session_id)->second.nextPage();
	}

	string prevPage(const string &session_id){
		return sessions.find(session_id)->second.prevPage();

	}

	string jmpToPage(const string &session_id, int new_idx_page){
		return sessions.find(session_id)->second.jmpToPage(new_idx_page);
	}

	void close(const string &session_id){
		sessions.find(session_id)->second.close();
	}
};

class InOutPuter{
	istream &in;
	ostream &out, &errs;

	void ignore(){
		in.ignore(numeric_limits<streamsize>::max(), '\n');
	}

public:
	InOutPuter(istream &in, ostream &out, ostream &errs): in(in), out(out), errs(errs) {}

	int getInt(){
		int ret;

		while(1){
			out << ">>:";
			in >> ret;

			if(!in.fail()) break;

			ignore();

			errs << "invalid input int, try again:";
		}
		return ret;
	}

	int getInt(int low, int high){
		int ret;
		while(1){
			out << ">>:";
			ret = getInt();
			if(ret >= low and ret <= high) break;
			errs << "out of range input, try again:";
		}
		return ret;
	}

	string getStr(){
		string ret;
		while(1){
			out << ">>:";
			in >> ret;

			if(!in.fail()) break;

			ignore();

			errs << "invalid input str, try again:";
		}

		return ret;
	}

	string getLineStr(){
		string ret;

		while(1){
			if(in.peek() == '\n'){
				in.ignore();
				continue;
			}
			out << ">>:";
			getline(in, ret);

			if(!in.fail()) break;

			ignore();

			errs << "invalid input str, try again:";
		}
		return ret;
	}


	void outLines(const vector<string> &lines){
		for(const auto &line : lines) cout << line << "\n";
	}

	int outLinesReadInt(const vector<string> &lines){
		outLines(lines);
		return getInt();
	}

	int outLinesReadInt(const vector<string> &lines, int low, int high){
		outLines(lines);
		return getInt(low, high);
	}

	string outLinesReadStr(const vector<string> &lines){
		outLines(lines);
		return getStr();
	}

	string outLinesReadLineStr(const vector<string> &lines){
		outLines(lines);
		return getLineStr();
	}

};

class System{
	map<string, Book>books;
	Admin admin;
	Customer customer;

	istream &in;
	ostream &out, &errs;
	InOutPuter iop;
public:
	System(istream &in_, ostream &out_, ostream &errs_): in(in_), out(out_), errs(errs_), iop(in_, out_, errs_){
		// load all Books to books
		books = Book::loadBooks();
	}

	void run(){
		signInUpMenue();
	}

	void signInUpMenue(){
		while(1){
			int choice = iop.outLinesReadInt({
				"0. Signin Admin", "1. Sign up customer", "2. Sign in customer"
			},0, 2);

			if(choice == 0) signInAdmin();
			else if(choice == 1) signUpCustomer();
			else signInCustomer();
		}
	}

	void signUpCustomer(){
		iop.outLines({"username", "email", "password"});
		const string &uname = iop.getStr();
		const string &email = iop.getStr();
		const string &pw = iop.getStr();
		if(customer.signUp(uname, email, pw)) mainCusMenue();
		else out << "can't sign up.\n";
	}

	void signInAdmin(){
		iop.outLines({"username", "password"});
		const string &uname = iop.getStr();
		const string &pw = iop.getStr();
		if(admin.login(uname, pw)) mainAdminMenue();
		else out << "can't login.\n";
	}

	void signInCustomer(){
		iop.outLines({"username", "password"});
		const string &uname = iop.getStr();
		const string &pw = iop.getStr();
		if(customer.login(uname, pw, books)) mainCusMenue();
		else out << "can't login.\n";
	}

	void mainAdminMenue(){
		while(1){
			int ch = iop.outLinesReadInt({"0. View Profile", "1. Add new book", "2. logout"}, 0, 2);
			if(ch == 0) out << admin.getInfo() << "\n";
			else if(ch == 1) addNewBookMenue();
			else{
				admin.logout();
				break;
			}
		}
	}

	void addNewBookMenue(){
		out << "book name\n";
		const string &name = iop.getLineStr();
		out << "book pages\n";
		const vector<string> &pages = Utils::str_to_vec<string>(iop.getLineStr());
		admin.addBook(name, pages, books);
	}

	void mainCusMenue(){
		while(1){
			int ch = iop.outLinesReadInt({
				"0. View Profile",
				"1. List system books",
				"2. List my Sessions", "3. Create Sessions", "4. Open Session","5. Remove Session",
				"6. logout"
			}, 0, 6);

			if(ch == 0) out << customer.getInfo() << "\n";
			else if(ch == 1){
				for(const auto kv : books)
					out << kv.ys.getInfo() << "\n";
			}
			else if(ch == 2) listSess();
			else if(ch == 3) createSess();
			else if(ch == 4) openSess();
			else if(ch == 5) removeSess();
			else{
				customer.logout();
				break;
			}
		}
	}

	void listSess (){
		iop.outLines(customer.getSesstionsInfo());
	}

	void createSess(){
		const string &book_id = iop.outLinesReadStr({"Enter Book Id"});
		out << "sess id: " << customer.createSession(books.find(book_id)->ys) << "\n";
	}

	void openSess(){
		const string &sess_id = iop.outLinesReadStr({"Enter Session Id"});
		out << "{\n";
		out << "<" << customer.openSession(sess_id) << ">" << endl;
		while(1){
			out << endl;
			int ch = iop.outLinesReadInt({"0. next page", "1. prev page", "2. jmp to page", "3. close"}, 0, 3);
			if(ch == 0) out << customer.nextPage(sess_id);
			else if(ch == 1) out << customer.prevPage(sess_id);
			else if(ch == 2){
				out << "Page #";
				out << customer.jmpToPage(sess_id, iop.getInt());
			}
			else break;
		}
		out << "}";
		cout << endl;
		customer.close(sess_id);
	}

	void removeSess(){
		const string &sess_id = iop.outLinesReadStr({"Enter Session Id"});
		customer.removeSession(sess_id);
	}
};

int main() {
//	file_r;

	System(cin, cout, cerr).run();
	return 0;
}
