#pragma once
#include <string.h>
#include <stdlib.h>
__WALIBC_BEGIN_EXTERN;

// Support the environment enough so that if you do a `setenv` and then a
// `getenv` of the same variable (say), the `getenv` will see the value set by
// the `setenv`.
//
// This code was mostly taken from musl.

char **environ = 0;

static void env_rm_add(char *old, char *new) {
	static char **env_alloced;
	static size_t env_alloced_n;
	for (size_t i=0; i < env_alloced_n; i++) {
		if (env_alloced[i] == old) {
			env_alloced[i] = new;
			free(old);
			return;
		} else if (!env_alloced[i] && new) {
			env_alloced[i] = new;
			new = 0;
		}
    }
	if (!new) return;
	char **t = realloc(env_alloced, sizeof *t * (env_alloced_n + 1));
	if (!t) return;
    env_alloced = t;
	t[env_alloced_n++] = new;
}

static int do_putenv(char *s, size_t l, char *r) {
	size_t i = 0;
	if (environ) {
		for (char **e = environ; *e; ++e, ++i) {
			if (!strncmp(s, *e, l + 1)) {
				char *tmp = *e;
				*e = s;
				env_rm_add(tmp, r);
				return 0;
			}
        }
	}
	static char **oldenv;
	char **newenv;
	if (environ == oldenv) {
		newenv = realloc(oldenv, sizeof(*newenv) * (i + 2));
		if (!newenv) goto oom;
	} else {
		newenv = malloc(sizeof(*newenv) * (i + 2));
		if (!newenv) goto oom;
		if (i) memcpy(newenv, environ, sizeof(*newenv) * i);
		free(oldenv);
	}
	newenv[i] = s;
	newenv[i + 1] = 0;
	environ = oldenv = newenv;
	if (r) env_rm_add(0, r);
	return 0;
oom:
	free(r);
	return -1;
}

char *__walibc_getenv(char const *name) {
    // Fast path: no env.
    if (!environ) return 0;
	size_t n = strchrnul(name, '=') - name;
	if (n && !name[n]) return 0;
    for (size_t i = 0; environ[i]; ++i)
        if (!strncmp(name, environ[i], n) && environ[i][n] == '=')
            return environ[i] + n + 1;
    return 0;
}

int __walibc_setenv(char const *var, char const *val, int overwrite) {
    char *s;
	size_t l1, l2;

	if (!var || !(l1 = strchrnul(var, '=') - var) || var[l1]) {
		errno = EINVAL;
		return -1;
	}
	if (!overwrite && getenv(var)) return 0;

	l2 = strlen(val);
	s = malloc(l1 + l2 + 2);
	if (!s) return -1;
	memcpy(s, var, l1);
	s[l1] = '=';
	memcpy(s + l1 + 1, val, l2 + 1);
	return do_putenv(s, l1, s);
}

int __walibc_unsetenv(char const *name) {
	size_t l = strchrnul(name, '=') - name;
	if (!l || name[l]) {
		errno = EINVAL;
		return -1;
	}
	if (environ) {
		char **e = environ, **eo = e;
		for (; *e; e++)
			if (!strncmp(name, *e, l) && l[*e] == '=')
				env_rm_add(*e, 0);
			else if (eo != e)
				*eo++ = *e;
			else
				eo++;
		if (eo != e) *eo = 0;
	}
	return 0;
}

int __walibc_putenv(char *s) {
	size_t l = strchrnul(s, '=') - s;
	if (!l || !s[l]) return unsetenv(s);
	return do_putenv(s, l, 0);
}

int __walibc_clearenv(void) {
	char **e = environ;
	environ = 0;
	if (e) while (*e) env_rm_add(*e++, 0);
	return 0;
}

__WALIBC_END_EXTERN;

