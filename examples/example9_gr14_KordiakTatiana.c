// Insert in TRANSACTION mode 

#include <stdio.h>
#include <sqlite3.h>

int main(void) {

	sqlite3 *db;
	char *ErrMsg = 0;
	char *sql;

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
	sql = "DROP TABLE IF EXISTS Class;" \
				"BEGIN TRANSACTION;" \
				"CREATE TABLE Class(Id INTEGER PRIMARY KEY, Name TEXT);" \
				"INSERT INTO Class(Name) VALUES ('Bob'),('Tom'),('Becca'),('Tess'),('Liz');" \
				"COMMIT"; 
	
	//Executing SQL statement
	rc = sqlite3_exec(db, sql, 0, 0, &ErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr,"SQL error: %s.\n", ErrMsg);
		
		sqlite3_free(ErrMsg);
		sqlite3_close(db);
		return 1;
	}
	
	sqlite3_close(db);

	return 0;
}
