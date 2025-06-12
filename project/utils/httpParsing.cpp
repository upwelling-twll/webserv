#include "../src/core/Connection.hpp"

parseMethod(_rawMessage);
if (_rstatus == HTTP_GET_METHOD)
    parseContentLength(_rawMessage);
if (_rstatus == PARSE_CONTENT_LENGTH_VALUE)
    parseContentLengthValue(_rawMessage);
if (_rstatus == RECEIVING_BODY)
    checkCurrentBodyLength(_rawMessage);
if (_rstatus == MORE_CHUNKS)
    checkMoreChunks(_rawMessage);