/*
 * Time.c
 * 
 * Copyright (c) 2006-2009 Operational Dynamics Consulting Pty Ltd
 * 
 * The code in this file, and the library it is a part of, are made available
 * to you by the authors under the terms of the "GNU General Public Licence,
 * version 2" plus the "Classpath Exception" (you may link to this code as a
 * library into other programs provided you don't make a derivation of it).
 * See the LICENCE file for the terms governing usage and redistribution.
 */

/*
 * This code imported from the SlashTime project's wrapper around the C time
 * functions at src/java/com/operationaldynamics/slashtime/Time.c
 */

#include <jni.h>
#include <stdlib.h>
#include <time.h>
#include <glib.h>
#include "bindings_java.h"
#include "oscats_bindings_Time.h"

#define MAXWIDTH 64


JNIEXPORT void JNICALL
Java_oscats_bindings_Time_tzset
(
	JNIEnv *env,
	jclass cls,
	jstring _zoneinfo
)
{
	/*
	 * Carry out the magic to switch zones by calling tzset(). It doesn't
	 * have parameters - it pulls TZ from the environment.
	 */

	const char *zoneinfo;
	int ok;

	zoneinfo = bindings_java_getString(env, _zoneinfo);
	if (zoneinfo == NULL) {
		return; /* OutOfMemoryError already thrown */
	}

	ok = g_setenv("TZ", zoneinfo, TRUE);

	bindings_java_releaseString(zoneinfo);
	if (ok != 0) {
		// throw exception
		return;
	}

	tzset();
}

JNIEXPORT jstring JNICALL
Java_oscats_bindings_Time_strftime
(
	JNIEnv *env,
	jclass klass,
	jstring _format,
	jlong _timestamp
)
{
	/*
	 * Call strftime() to generate the string in the desired format. We
	 * pass in size as the max, and the return value indicates how much was
	 * used.
	 */

	const char *format;
	size_t size;
	char buf[MAXWIDTH];
	struct tm *brokendown;
	time_t timestamp;

	size = MAXWIDTH;

	format = bindings_java_getString(env, _format);
	if (format == NULL) {
		return NULL; /* OutOfMemoryError already thrown */
	}

	timestamp = (time_t) _timestamp;

	brokendown = localtime(&timestamp);

	size = strftime(buf, size, format, brokendown);

	bindings_java_releaseString(format);
	if (size == 0) {
		// throw exception instead!
		return bindings_java_newString(env, "Nothing returned!\0");
	}

	return bindings_java_newString(env, buf);
}

JNIEXPORT jlong JNICALL
Java_oscats_bindings_Time_mktime
(
	JNIEnv *env,
	jclass cls,
	jint _year,
	jint _month,
	jint _day,
	jint _hour,
	jint _minute,
	jint _second
)
{
	struct tm brokendown = { 0, };
	time_t timestamp;

	brokendown.tm_year = _year - 1900;
	brokendown.tm_mon = _month - 1;
	brokendown.tm_mday = _day;
	brokendown.tm_hour = _hour;
	brokendown.tm_min = _minute;
	brokendown.tm_sec = _second;

	timestamp = mktime(&brokendown);

#ifdef DEBUG
	fprintf(stderr, "JNI: %s\n", g_getenv("TZ"));
	size_t size;
	char buf[MAXWIDTH];
	strftime(buf, size, "%a, %d %b %Y %H:%M:%S %z %Z", localtime(&timestamp));
	fprintf(stderr, "JNI: %d; %s and %d\n", (int) timestamp, buf, brokendown.tm_isdst);
	fflush(stderr);
#endif

	/*
	 * Bizarre bug that mktime adds an hour of DST to the displayed time if in DST.
	 */
	if (brokendown.tm_isdst == 1) {
		timestamp -= 3600;
	}
		
	return (jlong) timestamp;
}
