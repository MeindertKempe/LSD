#ifndef MACRO_H
#define MACRO_H
#pragma once

#ifdef __GNUC__
#	define UNUSED __attribute__((__unused__))
#else
#	define UNUSED
#endif

#endif /* MACRO_H */
