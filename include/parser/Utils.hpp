// #include "../Utils.hpp"
// #include "Location.hpp"

void			eraseCommand(string &args);
unsigned int	checkCountArgs(string &args);
string 			popBackArg(string &args);
void	parseListenPath(string &path, ListenPort & listen);
void	checkAddress(string &address);