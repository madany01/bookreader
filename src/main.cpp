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


class InOutPuter{
	istream &in;
	ostream &out, &errs;

	void ignore(){
		in.ignore(numeric_limits<streamsize>::max(), '\n');
	}

public:
	InOutPuter(istream &in=cin, ostream &out=cout, ostream &errs=cerr): in(in), out(out), errs(errs) {}

	int getInt(){
		int ret;

		while(1){
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
			ret = getInt();
			if(ret >= low and ret <= high) break;
			errs << "out of range input, try again:";
		}
		return ret;
	}

	string getLineStr(){
		string ret;

		if(in.peek() == '\n')
			in.ignore();

		while(1){
			getline(in, ret);

			if(!in.fail()) break;

			ignore();

			errs << "invalid input str, try again:";
		}
		return ret;
	}

	void putLines(const vector<string> &lines){
		for(const auto &line : lines) out << line << "\n";
		out << flush;
	}

	int putLinesGetAnyInt(const vector<string> &lines){
		putLines(lines);
		return getInt();
	}

	int putLinesGetInt(const vector<string> &lines){
		putLines(lines);
		return getInt(0, sz(lines));
	}

	string putLinesGetLineStr(const vector<string> &lines){
		putLines(lines);
		return getLineStr();
	}
};

class DirectoryManager{
	string dir_path;

	template <class TP>
	static time_t to_time_t(TP tp) {
	    using namespace chrono;
	    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now() + system_clock::now());
	    return system_clock::to_time_t(sctp);
	}
public:
	DirectoryManager(const string &dir_path): dir_path(dir_path) {}

	vector<string> getNamesWithoutExtension(){
		vector<string> names;
	    for (const auto & entry : fs::directory_iterator(dir_path))
	    	names.eb(entry.path().stem().string());
	    return names;
	}

	bool hasFile(const string &name, bool name_has_extension){
		if(name_has_extension) return fs::exists(gluePaths({dir_path, name}, ""));

		const auto &names = getNamesWithoutExtension();

		return find(all(names), name) != names.end();
	}

	void createFile(const string &name, const string &extension, const vector<string> &lines = {}){
		ofstream f;

		f.open(gluePaths({dir_path, name}, extension), ios::trunc);

		for(int i = 0; i < sz(lines); i++){
			if(i) f << "\n";
			f << lines[i];
		}
		f.close();
	}

	void updateFile(const string &name, const string &extension, const vector<string> &lines, bool app){
		if(not app){
			createFile(name, extension, lines);
			return ;
		}
		ofstream f;
		f.open(gluePaths({dir_path, name}, extension), ios::app);
		for(const auto &line : lines) f << "\n" << line;
		f << "\n";
		f.close();
	}

	vector<string> getFile(const string &name, const string &extension){
		ifstream f;
		f.open(gluePaths({dir_path, name}, extension));

		vector<string> lines;
		string buff;

		while(getline(f, buff)) lines.emplace_back(move(buff));

		f.close();
		return lines;
	}

	void removeFile(const string &name, const string &extension){
		fs::remove(gluePaths({dir_path, name}, extension));
	}

	string getModificationDate(const string &name, const string &extension){
		auto ftime = filesystem::last_write_time(gluePaths({dir_path, name}, extension));
		time_t cftime = to_time_t(ftime);
		return std::asctime(std::localtime(&cftime));
	}

	static string gluePaths(const vector<string>& paths, const string &extension){
		assert(sz(paths) > 0);

		auto glued_path_fs = fs::path(paths[0]);
		lp(i, 1, sz(paths)) glued_path_fs /= paths[i];
		
		string glued_path = glued_path_fs.string();
		
		if(not extension.empty())
			glued_path += extension;

		return glued_path;
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

	template<class type>
	static string vec_to_str(const vector<type> &v){
		string ret;
		lp_(a, v) ret += to_string(a) + " ";
		if(not ret.empty()) ret.pop_back();
		return ret;
	}

	static string vec_to_str(const vector<string> &v){
		string ret;
		lp_(a, v) ret += a + " ";
		if(not ret.empty()) ret.pop_back();
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
	string id;
	string name;
	vector<string> pages;
	string load_date, last_modify_date;

	void fill(const vector<string>& fileLines, const string &file_modify_date_){
		load_date = last_modify_date = file_modify_date_;
		tie(id, name) = mkt(fileLines[0], fileLines[1]);
		pages = vector<string>(begin(fileLines)+2, end(fileLines));
	}

public:
	Book(const vector<string>& fileLines, const string &file_modify_date_){
		fill(fileLines, file_modify_date_);
	}

	Book(const string &name, const vector<string> &pages):
		id(Utils::getRnd()), name(name), pages(pages){
	}

	void assign(const vector<string> &fileLines, const string &file_modify_date){
		fill(fileLines, file_modify_date);
	}

	void setLoadDate(const string &date){
		load_date = date;
	}

	void setLastModifyDate(const string &date){
		last_modify_date = date;
	}

	const string& getId() const {
		return id;
	}

	int getPageCnt() const {
		return sz(pages);
	}

	void setName(const string &new_name){
		name = new_name;
		last_modify_date = Utils::getDate();
	}

	const string& getName() const {
		return name;
	}

	const string& getPage(int idx) const {
		assert(idx > -1 and idx < sz(pages));
		return pages[idx];
	}

	const string& getLoadDate() const {
		return load_date;
	}

	const string& getLastModifyDate() const {
		return last_modify_date;
	}

	string toString() const {
		ostringstream oss;
		oss << "Book[" << id << "]" << ": " << "name: " << name << " " << "#pages = " << sz(pages);
		return oss.str();
	}

	bool isChanged() const {
		assert(!load_date.empty());
		assert(!last_modify_date.empty());
		return getLastModifyDate() != getLoadDate();
	}

	vector<string> getTXTFileRepresentation() const {
		vector<string> fileLines = {id, name};
		lp(i, 0, sz(pages)) fileLines.emplace_back(pages[i]);
		return fileLines;
	}
};

class BooksManager{
	inline static const string path_dir_books_man = (fs::current_path() / "DB" / "BooksManager").string();
	inline static const string extension = ".txt";

	map<string, Book> books; // [book_id, Book]
	DirectoryManager dir_man;

	void loadDB(){
		for(const string &book_id : dir_man.getNamesWithoutExtension())
			books.emplace(book_id, Book(dir_man.getFile(book_id, extension), dir_man.getModificationDate(book_id, extension)));
	}

	void loadNewBooks(){
		lp_(book_id, dir_man.getNamesWithoutExtension())
			if(not books.contains(book_id))
				books.emplace(book_id, Book(dir_man.getFile(book_id, extension), dir_man.getModificationDate(book_id, extension)));
	}

	void removeDeletedBooks(){
		vector<string> book_ids {dir_man.getNamesWithoutExtension()};
		sort(all(book_ids));

		vector<string> to_del;

		lp_(kv, books)
			if(!binary_search(all(book_ids), kv.first))
				to_del.emplace_back(kv.first);

		lp_(book_id, to_del)
			books.erase(book_id);
	}

	void loadChangedBooks(){
		for(auto &kv : books){
			const string &book_id = kv.first;
			Book &book = kv.second;
			const string &file_modify_date = dir_man.getModificationDate(book_id, extension);

			if(file_modify_date == book.getLoadDate()) continue;

			book.assign(dir_man.getFile(book_id, extension), dir_man.getModificationDate(book_id, extension));
		}
	}

	void saveChangedBooks(){
		for(auto &kv : books){
			const string &book_id = kv.first;
			Book &book = kv.second;
			const string &file_modify_date = dir_man.getModificationDate(book_id, extension);

			if(file_modify_date == book.getLoadDate() and book.isChanged())
				dir_man.updateFile(book_id, extension, book.getTXTFileRepresentation(), 0);
		}
	}
public:
	BooksManager(): dir_man(path_dir_books_man) {
		loadDB();
	}

	void addBook(const Book &book){
		refreshDB();
		assert(not dir_man.hasFile(book.getId(), ".txt"));

		dir_man.createFile(book.getId(), ".txt", book.getTXTFileRepresentation());
		const string &date = dir_man.getModificationDate(book.getId(), extension);
		auto it = books.emplace(book.getId(), book);
		it.first->second.setLoadDate(date);
		it.first->second.setLastModifyDate(date);
	}

	void removeBook(const string &book_id){
		refreshDB();
		auto it = books.find(book_id);
		assert(it != end(books));
		const Book &book = it->ys;
		dir_man.removeFile(book.getId(), ".txt");
		books.erase(it);
	}

	Book& getBook(const string &book_id){
		refreshDB();
		assert(books.contains(book_id));
		return books.find(book_id)->second;
	}

	void refreshDB(){
		removeDeletedBooks();
		loadNewBooks();
		loadChangedBooks();
		saveChangedBooks();
	}

	bool hasBook(const string &book_id){
		refreshDB();
		return books.contains(book_id);
	}

	vector<string> getBooksInfo(){
		refreshDB();
		vector<string> books_info;
		for(const auto &pair : books)
			books_info.emplace_back(pair.ys.toString());
		return books_info;
	}
};

class Session{
	string id;
	string book_id;
	BooksManager &books_man;
	int page_idx;
	string last_view_date;
	string load_date, last_modify_date;

	void resetViewDate(){
		last_view_date = Utils::getDate();
	}

	void resetModifyDate(){
		last_modify_date = Utils::getDate();
	}
public:
	Session(const string &book_id, BooksManager &books_man): id(Utils::getRnd()), book_id(book_id), books_man(books_man), page_idx(0){
		resetViewDate();
	}

	Session(const vector<string> &fileLines, BooksManager &books_man, const string &file_load_date): books_man(books_man){
		tie(id, book_id, page_idx, last_view_date) = mkt(fileLines[0], fileLines[1], stoi(fileLines[2]), fileLines[3]);
		setLoadDate(file_load_date);
		setLastModifyDate(file_load_date);
	}

	void setLoadDate(const string &date){
		load_date = date;
	}

	void setLastModifyDate(const string &date){
		last_modify_date = date;
	}

	const string& getId() const {
		return id;
	}

	const string &getLoadDate() const {
		return load_date;
	}

	const string &getLastModifyDate() const {
		return last_modify_date;
	}

	const string& open(){
		resetViewDate();
		resetModifyDate();
		return books_man.getBook(book_id).getPage(page_idx);
	}

	const string& nextPage(){
		resetViewDate();
		resetModifyDate();
		return books_man.getBook(book_id).getPage(++page_idx);
	}

	const string& prevPage(){
		resetViewDate();
		resetModifyDate();
		return books_man.getBook(book_id).getPage(--page_idx);
	}

	const string& jmpToPage(int to_idx){
		resetViewDate();
		resetModifyDate();
		return books_man.getBook(book_id).getPage(page_idx=to_idx);
	}

	bool isChanged() const {
		assert(!load_date.empty());
		assert(!last_modify_date.empty());
		return getLastModifyDate() != getLoadDate();
	}

	string toString() const {
		ostringstream oss;
		oss << "Sess [" << id << "]" << ": " << "on book [" << books_man.getBook(book_id).getId() << "]" << " " << "page:" << page_idx << "\\"
				<< books_man.getBook(book_id).getPageCnt() << " " << "last view on " << last_view_date;
		return oss.str();
	}

	vector<string> getTXTFileRepresentation() const {
		return {id, book_id, to_string(page_idx), last_view_date};
	}

};

class SessionManager{
	inline static const string path_dir_sess_man = (fs::current_path() / "DB" / "SessionManager").string();
	
	inline static const string extension = ".txt";

	map<string, Session> sessions;
	BooksManager &books_man;
	DirectoryManager dir_man;

	void loadDB(){
		for(const auto &sess_id : dir_man.getNamesWithoutExtension())
			sessions.emplace(sess_id, Session(dir_man.getFile(sess_id, extension), books_man, dir_man.getModificationDate(sess_id, extension)));
	}

public:

	SessionManager(BooksManager &books_man): books_man(books_man), dir_man(path_dir_sess_man){
		loadDB();
	}

	void addSession(const Session &sess){
		assert(not sessions.contains(sess.getId()));

		dir_man.createFile(sess.getId(), extension, sess.getTXTFileRepresentation());

		const string &date = dir_man.getModificationDate(sess.getId(), extension);

		Session &added_sess = sessions.emplace(sess.getId(), sess).first->second;
		added_sess.setLoadDate(date);
		added_sess.setLastModifyDate(date);
	}

	// save explicitly your changes when it's completed.
	void saveChanges(const string &sess_id){
		assert(sessions.contains(sess_id));
		Session &sess = sessions.find(sess_id)->second;
		dir_man.updateFile(sess_id, extension, sess.getTXTFileRepresentation(), 0);
		const string &date = dir_man.getModificationDate(sess_id, extension);
		sess.setLoadDate(date);
		sess.setLastModifyDate(date);
	}

	void removeSession(const string &sess_id){
		assert(sessions.contains(sess_id));

		dir_man.removeFile(sess_id, extension);
		sessions.erase(sess_id);
	}

	bool hasSession(const string &sess_id) const {
		return sessions.contains(sess_id);
	}

	Session& getSession(const string &sess_id){
		assert(sessions.contains(sess_id));
		return sessions.find(sess_id)->second;
	}

};

class User{
	string id;
	string uname;
	string password;
public:
	User(const string &uname, const string &password): id(Utils::getRnd()), uname(uname), password(password){
	}

	User(const vector<string> &fileLines){
		tie(id, uname, password) = mkt(fileLines[0], fileLines[1], fileLines[2]);
	}

	const string& getId() const {
		return id;
	}

	const string& getPassword() const {
		return password;
	}

	const string& getUsername() const {
		return uname;
	}

	string toString() const {
		ostringstream oss;
		oss << "id [" << id << "]" << ": " << uname << " " << password;
		return oss.str();
	}

	vector<string> getTXTFileRepresentation() const {
		return {id, uname, password};
	}
};

class Customer : public User{
	SessionManager &sess_man;
	set<string> sess_ids;
	bool is_changed = 0;

public:
	Customer(const User &user, SessionManager &sess_man): User(user), sess_man(sess_man){
	}

	Customer(const vector<string> &fileLines, SessionManager &sess_man):
		User(vector<string>(begin(fileLines)+1+stoi(fileLines[0]), end(fileLines))), sess_man(sess_man){
		sess_ids = set<string>(begin(fileLines)+1, begin(fileLines)+1+stoi(fileLines[0]));
	}

	void setIsChanged(bool state){
		is_changed = state;
	}

	bool isChanged() const {
		return is_changed;
	}

	void addSession(const Session &sess){
		sess_man.addSession(sess);
		sess_ids.emplace(sess.getId());
		setIsChanged(1);
	}

	void removeSession(const string &sess_id){
		assert(sess_ids.contains(sess_id));
		sess_man.removeSession(sess_id);
		sess_ids.erase(sess_id);
		setIsChanged(1);
	}

	void removeAllData(){
		for(const auto &sess_id : sess_ids)
			sess_man.removeSession(sess_id);
		sess_ids.clear();
		setIsChanged(1);
	}

	Session& getSession(const string &sess_id){
		assert(sess_ids.contains(sess_id));
		return sess_man.getSession(sess_id);
	}

	void saveChanges(const string &sess_id){
		assert(sess_ids.contains(sess_id));
		sess_man.saveChanges(sess_id);
	}

	int getSessCnt() const {
		return sz(sess_ids);
	}

	vector<string> getSessionsInfo() const {
		vector<string> lines;
		for(const auto &sess_id : sess_ids)
			lines.emplace_back(sess_man.getSession(sess_id).toString());
		return lines;
	}

	vector<string> getTXTFileRepresentation() const {
		vector<string> fileLines;
		fileLines.emplace_back(to_string(sz(sess_ids)));
		for(const auto &sess_id : sess_ids)
			fileLines.emplace_back(sess_id);
		lp_(line, User::getTXTFileRepresentation()) fileLines.emplace_back(line);
		return fileLines;
	}
};

class CustomersManager{
	inline static const string path_dir_cus_man = (fs::current_path() / "DB" / "CustomersManager").string();
	inline static const string extension = ".txt";

	map<string, Customer> customers; // handled here
	SessionManager &sess_man;
	DirectoryManager dir_man;

	void loadDB(){
		for(const auto &cus_id : dir_man.getNamesWithoutExtension())
			customers.emplace(cus_id, Customer(dir_man.getFile(cus_id, extension), sess_man));
	}

public:
	CustomersManager(SessionManager &sess_man): sess_man(sess_man), dir_man(path_dir_cus_man){
		loadDB();
	}

	pair<bool, string> addCustomer(const User &user){
		if(customers.contains(user.getId())) return {0, {}};
		const auto &cus = customers.emplace(user.getId(), Customer(user, sess_man)).first->second;
		dir_man.createFile(cus.getId(), extension, cus.getTXTFileRepresentation());
		return {1, cus.getId()};
	}

	bool hasCustomer(const string &cus_id) const {
		return customers.contains(cus_id);
	}

	Customer& getCustomer(const string &cus_id){
		assert(hasCustomer(cus_id));
		return customers.find(cus_id)->second;
	}


	void saveChanges(const string &cus_id){
		assert(hasCustomer(cus_id));
		Customer &cus = customers.find(cus_id)->second;
		if(!cus.isChanged()) return;
		dir_man.updateFile(cus_id, extension, cus.getTXTFileRepresentation(), 0);
		cus.setIsChanged(0);
	}

	void removeCustomer(const string &customer_id){
		assert(hasCustomer(customer_id));

		dir_man.removeFile(customer_id, extension);
		customers.find(customer_id)->second.removeAllData();
		customers.erase(customer_id);
	}

};

class Admin : public User{
	BooksManager &books_man;
public:
	Admin(const User &user, BooksManager &books_man): User(user), books_man(books_man) {}

	Admin(const vector<string> &fileLines, BooksManager &books_man): User(fileLines), books_man(books_man) {}

	void addBook(const Book &book){
		books_man.addBook(book);
	}

	void removeBook(const string &book_id){
		books_man.removeBook(book_id);
	}
};

class AdminsManager{
	inline static const string path_dir_admins_man = (fs::current_path() / "DB" / "AdminsManager").string();
	inline static const string extension = ".txt";
	map<string, Admin> admins;
	BooksManager &books_man;
	DirectoryManager dir_man;

	void loadDB(){
		for(const auto &cus_id : dir_man.getNamesWithoutExtension())
			admins.emplace(cus_id, Admin(dir_man.getFile(cus_id, extension), books_man));
	}

public:
	AdminsManager(BooksManager &books_man): books_man(books_man), dir_man(path_dir_admins_man){
		loadDB();
	}

	Admin& getAdmin(const string &admin_id){
		return admins.find(admin_id)->ys;
	}
	bool hasAdmin(const string &admin_id) const {
		return admins.contains(admin_id);
	}
	pair<bool, string> addAdmin(const User &user){
		if(hasAdmin(user.getId())) return {0, ""};
		Admin &admin = admins.emplace(user.getId(), Admin(user, books_man)).first->second;
		dir_man.createFile(admin.getId(), extension, admin.getTXTFileRepresentation());
		return {1, user.getId()};
	}

	void removeAdmin(const string &admin_id){
		dir_man.removeFile(admin_id, extension);
		admins.erase(admin_id);
	}
};

class CustomerView{
	BooksManager &books_man;
	CustomersManager &cust_man;
	InOutPuter &iop;
public:
	CustomerView(BooksManager &books_man, CustomersManager &cust_man, InOutPuter &iop):
		books_man(books_man), cust_man(cust_man), iop(iop){
	}

	void view(){
		while(1){
			int ch = iop.putLinesGetInt({"0. SignUp", "1. Login", "2. back"});

			if(ch == 0) signUp();
			else if(ch == 1) logIn();
			else break;
		}
	}

	void signUp(){
		while(1){
			string cus_id;
			istringstream iss {iop.putLinesGetLineStr({"Enter username password separated by space(s):"})};
			string uname, pw;
			iss >> uname >> pw;

			pair<bool, string> res = cust_man.addCustomer(User(uname, pw));

			if(res.first){
				mainMenue(res.second);
				break;
			}
			else cerr << "Can't SignUp .. try again:";
		}
	}

	void mainMenue(const string &cus_id){
		while(1){
			int ch = iop.putLinesGetInt({
				"0. View Profile",
				"1. List system books",
				"2. List my Sessions", "3. Create Sessions", "4. Open Session","5. Remove Session",
				"6. logout"
			});

			if(ch == 0){
				cout << cust_man.getCustomer(cus_id).toString() << endl;
			}
			else if(ch == 1){
				for(const auto &str : books_man.getBooksInfo())
					cout << str << "\n";
				cout << flush;
			}
			else if(ch == 2){
				iop.putLines(cust_man.getCustomer(cus_id).getSessionsInfo());
			}
			else if(ch == 3) createSess(cus_id);
			else if(ch == 4) openSess(cus_id);
			else if(ch == 5) removeSess(cus_id);
			else break;
		}
	}

	void createSess(const string &cus_id){
		string book_id = iop.putLinesGetLineStr({"Enter Book id"});
		cust_man.getCustomer(cus_id).addSession(Session(book_id, books_man));
		cust_man.saveChanges(cus_id);
	}

	void removeSess(const string &cus_id){
		string sess_id = iop.putLinesGetLineStr({"Enter Session id"});
		cust_man.getCustomer(cus_id).removeSession(sess_id);
		cust_man.saveChanges(cus_id);
	}

	void openSess(const string &cus_id){
		string sess_id = iop.putLinesGetLineStr({"Enter Session id"});

		cout << endl;
		cout << cust_man.getCustomer(cus_id).getSession(sess_id).open();
		while(1){
			cout << endl;
			int ch = iop.putLinesGetInt({"0. next", "1. prev", "2. jmp", "3. close"});

			if(ch == 0){
				cout << cust_man.getCustomer(cus_id).getSession(sess_id).nextPage() << endl;
			}
			else if(ch == 1){
				cout << cust_man.getCustomer(cus_id).getSession(sess_id).prevPage() << endl;
			}
			else if(ch == 2){
				int page_idx = iop.putLinesGetAnyInt({"Enter page index:"});
				cout << cust_man.getCustomer(cus_id).getSession(sess_id).jmpToPage(page_idx) << endl;
			}
			else{
				break;
			}
		}
		cust_man.getCustomer(cus_id).saveChanges(sess_id);
	}

	void logIn(){
		while(1){
			istringstream iss {iop.putLinesGetLineStr({"Enter id password separated by space(s):"})};
			string cus_id, pw;
			iss >> cus_id >> pw;

			if(!cust_man.hasCustomer(cus_id) or cust_man.getCustomer(cus_id).getPassword() != pw){
				cerr << "Can't SignUp .. try again:";
				continue;
			}
			mainMenue(cus_id);
			break;
		}
	}
};

class AdminView{
	BooksManager &books_man;
	AdminsManager &adm_man;
	InOutPuter &iop;
public:
	AdminView(BooksManager &books_man, AdminsManager &admins_man, InOutPuter &iop): books_man(books_man), adm_man(admins_man), iop(iop) {}

	void view(){
		while(1){
			int ch = iop.putLinesGetInt({"0. SignUp", "1. Login", "2. back"});

			if(ch == 0) signUp();
			else if(ch == 1) logIn();
			else break;
		}
	}

	void signUp(){
		while(1){
			string adm_id;
			istringstream iss {iop.putLinesGetLineStr({"Enter username password separated by space(s):"})};
			string uname, pw;
			iss >> uname >> pw;

			pair<bool, string> res = adm_man.addAdmin(User(uname, pw));

			if(res.first){
				mainMenue(res.second);
				break;
			}
			else cerr << "Can't SignUp .. try again:";
		}
	}

	void mainMenue(const string &adm_id){
		while(1){
			int ch = iop.putLinesGetInt({
				"0. View Profile",
				"1. List system books",
				"2. Add new book",
				"3. delete a book",
				"4. logout"
			});

			if(ch == 0){
				cout << adm_man.getAdmin(adm_id).toString() << endl;
			}
			else if(ch == 1){
				for(const auto &str : books_man.getBooksInfo())
					cout << str << "\n";
				cout << flush;
			}
			else if(ch == 2){
				addBook(adm_id);
			}
			else if(ch == 3){
				delBook(adm_id);
			}
			else break;
		}
	}

	void addBook(const string &adm_id){
		string name = iop.putLinesGetLineStr({"Enter book name"});
		vector<string> pages = Utils::str_to_vec<string>(iop.putLinesGetLineStr({"Enter book pages"}));
		adm_man.getAdmin(adm_id).addBook(Book(name, pages));
	}

	void delBook(const string &adm_id){
		string book_id = iop.putLinesGetLineStr({"Enter book id"});
		books_man.removeBook(book_id);
	}

	void logIn(){
		while(1){
			istringstream iss {iop.putLinesGetLineStr({"Enter id password separated by space(s):"})};
			string adm_id, pw;
			iss >> adm_id >> pw;

			if(!adm_man.hasAdmin(adm_id) or adm_man.getAdmin(adm_id).getPassword() != pw){
				cerr << "Can't SignUp .. try again:";
				continue;
			}
			mainMenue(adm_id);
			break;
		}
	}

};

class System{
	BooksManager books_man;
	SessionManager sess_man;
	CustomersManager cust_man;
	AdminsManager admn_man;
	InOutPuter iop;
public:
	System(): sess_man(books_man), cust_man(sess_man), admn_man(books_man){

	}

	void run(){
		while(1){
			int ch = iop.putLinesGetInt({"0. Customers", "1. Admins"});
			if(ch == 0) CustomerView(books_man, cust_man, iop).view();
			else AdminView(books_man, admn_man, iop).view();
		}
	}
};


int main() {
	System().run();
	return 0;
}
