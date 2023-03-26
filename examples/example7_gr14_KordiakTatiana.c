// Parameterized queries

#include <stdio.h>
#include <sqlite3.h>

int main(void) {

	sqlite3 *db;
	char *ErrMsg = 0;
	char *sql;
	sqlite3_stmt *res;

	int rc = sqlite3_open("test.db", &db);

	// Opening DB
	rc = sqlite3_open("test.db", &db);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error while opening db: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;	
	} else {
		fprintf(stdout,"Database opened successfully\n");
	}

	// Creating SQL statement
	sql = "SELECT Id, Name FROM Cars WHERE Id = 1"; 
	
	
	//Executing SQL statement
	rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

	if (rc == SQLITE_OK) {
		sqlite3_bind_int(res, 1, 3);
	} else {
		fprintf(stderr,"Statement execution failed: %s.\n", sqlite3_errmsg(db));
	}

	int step = sqlite3_step(res);

	if (step == SQLITE_ROW) {
		printf("%s: ", sqlite3_column_text(res, 0));
		printf("%s\n", sqlite3_column_text(res, 1));
	} else {
		fprintf(stderr,"Steps execution failed: %s.\n", sqlite3_errmsg(db));
	}
	
	sqlite3_finalize(res);
	sqlite3_close(db);

	return 0;
}
