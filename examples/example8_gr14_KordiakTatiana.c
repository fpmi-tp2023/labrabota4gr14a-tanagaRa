// Insert an image

#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char **argv) {

	FILE *fp = fopen("../image/rainbow.jpg", "rb");

	if (fp == NULL) {
		fprintf(stderr, "Error while opening file.\n");
		return 1;
	}

	fseek(fp, 0, SEEK_END);
	
	if (ferror(fp)) {
		fprintf(stderr, "fseek() failed\n");
		int r = fclose(fp);

		if (r == EOF) {
			fprintf(stderr, "File handler cannot close\n");
		}
		return 1;
	}

	int flen = ftell(fp);

	if (flen == -1) {
		perror("error occured");
		int r = fclose(fp);

		if (r == EOF) {
			fprintf(stderr, "File handler cannot close\n");
		}

		return 1;
	}
	
	fseek(fp, 0, SEEK_SET);
	
	if (ferror(fp)) {
		fprintf(stderr, "fseek() failed\n");
		int r = fclose(fp);

		if (r == EOF) {
			fprintf(stderr, "File handler cannot close\n");
		}
		return 1;
	}
	
	char data[flen+1];
	int size = fread(data, 1, flen, fp);
	
	if (ferror(fp)) {
		fprintf(stderr, "fseek() failed\n");
		int r = fclose(fp);

		if (r == EOF) {
			fprintf(stderr, "File handler cannot close\n");
		}
		return 1;
	}
	
	int r = fclose(fp);

	if (r == EOF) {
		fprintf(stderr, "File handler cannot close\n");
	}

	sqlite3 *db;
	char *ErrMsg = 0;
	char *sql;
	sqlite3_stmt *pStmt;

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
	sql = "INSERT INTO IMAGES(DATA) VALUES(?)"; 
	
	
	//Executing SQL statement
	rc = sqlite3_prepare(db, sql, -1, &pStmt, 0);

	if (rc != SQLITE_OK) {
		fprintf(stderr,"Statement preparation failed: %s.\n", sqlite3_errmsg(db));
		return 1;
	}
	
	sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);
	
	rc = sqlite3_step(pStmt);
	
	if (rc != SQLITE_DONE) {
		fprintf(stderr,"Execution failed: %s.\n", sqlite3_errmsg(db));
	}
	
	sqlite3_finalize(pStmt);
	sqlite3_close(db);

	return 0;
}
