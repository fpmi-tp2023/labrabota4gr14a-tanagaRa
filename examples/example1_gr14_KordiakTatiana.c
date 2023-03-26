// Example of connecting BD


#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char* argv[]) {
	sqlite3 *db;
	char ErrMsg = 0;
	int check;

	check = sqlite3_open("test.db", &db);

	if (check) {
		fprintf(stderr, "Error while opening database: %s\n", sqlite3_errmsg(db));
		return 0;
	} else {
		fprintf(stderr, "Database opened successfully\n");
	}

	sqlite3_close(db);
	return 0;
}
