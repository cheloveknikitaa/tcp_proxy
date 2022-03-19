#include "Utils.hpp"

int Socket(int domain, int type, int protocol){
	int res = socket(domain, type, protocol);
	if (res == -1) {
		throw runtime_error(string("Socket: ") + strerror(errno));
	}
	int yes = 1;
	setsockopt(res, SOL_SOCKET, SO_REUSEADDR, &yes, (socklen_t)(sizeof(yes)));
	return res;
}

int Bind(int socket, const struct sockaddr *address,
		socklen_t address_len) {
	int res = bind(socket, address, address_len);
	if (res == -1) {
		throw runtime_error(string("Bind: ") + strerror(errno));
	}
	return res;
}

int Listen(int socket, int backlog){
	int res = listen(socket, backlog);
	if (res == -1) {
		throw runtime_error(string("Listen: ") + strerror(errno));
	}
	return res;
}

int Accept(int socket, struct sockaddr *address,
		   socklen_t *address_len){
	int res = accept(socket, address, address_len);
	if (res == -1) {
//		throw runtime_error(string("Accept: ") + strerror(errno));
	}
	return res;
}

int Connect(int socket, struct sockaddr *address,
			socklen_t address_len){
    int res = connect(socket, address, address_len);
    if (res == -1) {
        throw runtime_error(string("Connect: ") + strerror(errno));
    }
    return res;
}

int Inet_pton(int af, const char *src, void *dst){
	int res = inet_pton(af, src, dst);
	if (res == -1) {
		throw runtime_error(string("Inet_pton: ") + strerror(errno));
	} else if (res == 0) {
		throw runtime_error(string("Inet_pton: the address was not parseable in the specified address family"));
	}
    return res;
}

int Inet_aton(const char *cp, struct in_addr &inp){
	int res = inet_aton(cp, &inp);
	if (res == -1) {
		throw runtime_error(string("Inet_aton: ") + strerror(errno));
	}
	return res;
}

void init_adr(struct sockaddr_in &adr, int port){
	memset(&adr, 0, sizeof adr);
	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
}

void Fcntl(int fd){
	int flag = fcntl(fd, F_GETFL);
	int res = fcntl(fd, F_SETFD, flag | O_NONBLOCK);
	if (res == -1) {
		throw runtime_error(string("fcntl: ") + strerror(errno));
	}
}

string Recv(int fd, ssize_t &nread){
	char buf[BUFFER_SIZE] = { 0 };
	nread = recv(fd, buf, BUFFER_SIZE - 1, MSG_NOSIGNAL);
	cout << "read byte: " << nread << "\n";
	if (nread == -1) {
		throw runtime_error(string("Recv: ") + strerror(errno));
	} else if (nread == 0) {
		throw fd;
	}
	return buf;
}

void Send(int fd, string msg, ssize_t &send_byte ) {
	if (send_byte == 0)
		send_byte = msg.size();
	cout << "Send msg: " << msg.c_str() << " byte: " << msg.size() << "\n";
	ssize_t res = send(fd, msg.c_str(), msg.size() , MSG_NOSIGNAL);
	if (res == -1) {
		throw runtime_error(string("Send: ") + strerror(errno));
	}
	send_byte -= res;
	cout << "send_byte after send: " << send_byte << "\n";
}

void sigHendler(int signum){
	if (signum == SIGINT ||
		signum == SIGTERM){
		exit(EXIT_SUCCESS);
	}
}

void createLog(string str, string ip, string port) {
	time_t now = time(0);
	char* dt = ctime(&now);
	ofstream file;
	file.open("log.txt", ios::app);
	if (file.is_open() == false) {
		throw runtime_error(string("log.txt: ") + strerror(errno));
	}
	file << "<>+++<>\n" + string(dt) + ip + ":" + port + "\n" + str + "<>---<>\n";
	file.close();
}

int containsSql(string str){
	static const vector<string>sql = { "ADD", "ALL", "ALTER", "AND", "ANY", "AS", "ASC", "BACKUP", "BETWEEN", "CASE", "CHECK", "COLUMN", "CONSTRAINT", "CREATE", "DATABASE", "DEFAULT", "DELETE", "DESC", "DISTINCT", "DROP", "EXEC", "EXISTS", "FOREIGN KEY", "FROM", "FULL", "GROUP BY", "HAVING", "IN", "INDEX", "INNER", "INSERT", "IS NULL", "IS NOT NULL", "JOIN", "LEFT JOIN", "LIKE", "LIMIT", "NOT", "NOT NULL", "OR", "ORDER BY", "OUTER JOIN", "PRIMARY KEY", "PROCEDURE", "RIGHT JOIN", "ROWNUM", "SELECT", "SET", "TABLE", "TOP", "TRUNCATE", "UNION", "UNIQUE", "UPDATE", "VALUES", "VIEW", "WHERE" };
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){ return std::toupper(c); } );
	for(auto cmd = sql.begin(); cmd != sql.end(); ++cmd){
		if (strstr(str.c_str(), cmd->c_str()))
			return 1;
	}
	return 0;
}

