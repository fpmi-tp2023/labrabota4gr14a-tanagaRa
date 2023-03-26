// Metadata output

#include <stdio.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main(void) {

	sqlite3 *db;
	char *ErrMsg = 0;
	char *sql;

	// Opening DB
	int rc = sqlite3_open("test.db", &db);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "Error while opening db: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;	
	} else {
		fprintf(stdout,"Database opened successfully\n");
	}

	// Creating SQL statement
	sql = "PRAGMA table_info(Cars)"; 
	
	//Executing SQL statement
	rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr,"Failed to select data\n");
		fprintf(stderr,"SQL error: %s.\n", ErrMsg);
		
		sqlite3_free(ErrMsg);
		sqlite3_close(db);
		return 1;
	}
	
	// Creating SQL statement
	sql = "SELECT name FROM sqlite_master WHERE type = 'table'"; 
	
	//Executing SQL statement
	rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr,"Failed to select data\n");
		fprintf(stderr,"SQL error: %s.\n", ErrMsg);
		
		sqlite3_free(ErrMsg);
		sqlite3_close(db);
		return 1;
	}
	sqlite3_close(db);

	return 0;
}
