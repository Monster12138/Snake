/* Copyright Abandoned 1996,1999 TCX DataKonsult AB & Monty Program KB
   & Detron HB, 1996, 1999-2004, 2007 MySQL AB.
   This file is public domain and comes with NO WARRANTY of any kind
*/

/* Version numbers for protocol & mysqld */

#ifndef _mysql_version_h
#define _mysql_version_h

#define PROTOCOL_VERSION            10
#define MYSQL_SERVER_VERSION       "5.7.21"
#define MYSQL_BASE_VERSION         "mysqld-5.7"
#define MYSQL_SERVER_SUFFIX_DEF    "-1"
#define FRM_VER                     6
#define MYSQL_VERSION_ID            50721
#define MYSQL_PORT                  3306
#define MYSQL_PORT_DEFAULT          0
#define MYSQL_UNIX_ADDR            "/var/run/mysqld/mysqld.sock"
#define MYSQL_CONFIG_NAME          "my"
#define MYSQL_COMPILATION_COMMENT  "(Debian)"
#define LIBMYSQL_VERSION           "5.7.21"
#define LIBMYSQL_VERSION_ID         50721
#define SYS_SCHEMA_VERSION         "1.5.1"

#ifndef LICENSE
#define LICENSE                     GPL
#endif /* LICENSE */

#endif /* _mysql_version_h */