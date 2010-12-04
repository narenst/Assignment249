/*
 *  Exceptions.h
 *  Assignment2_Xcode
 *
 *  Created by Rajagopal Sathyamurthi on 12/4/10.
 *  Copyright 2010 Stanford University. All rights reserved.
 *
 */
#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <string>

using namespace std;


class Exception {
	
public:
	Exception(const string& msg) : msg_(msg) {}
	~Exception( ) {}
	
	string getMessage( ) const {return(msg_);}
protected:
	
	string msg_;
};

class SegmentInUseException : public Exception {
public:
	SegmentInUseException( const string&  msg_) : Exception(msg_) {}
	~SegmentInUseException() {}
};

class NotConnectedException : public Exception {
public:
	NotConnectedException( const string&  msg_) : Exception(msg_) {}
	~NotConnectedException() {}
};

#endif