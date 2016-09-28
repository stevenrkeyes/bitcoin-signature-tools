#ifndef _verifymessage_h
#define _verifymessage_h

#include <string>
#include "util.h"
#include "base58.h"
#include "verifymessage.h"

extern const string strMessageMagic;

bool verifymessage(string strAddress, string strSign, string strMessage) {

    CBitcoinAddress addr(strAddress);
    if (!addr.IsValid()) {
        fprintf(stderr, "Invalid address\n");
        return 2;
    }

    CKeyID keyID;
    if (!addr.GetKeyID(keyID)) {
        fprintf(stderr, "Address does not refer to key\n");
        return 3;
    }

    bool fInvalid = false;
    vector<unsigned char> vchSig = DecodeBase64(strSign.c_str(), &fInvalid);

    if (fInvalid) {
        fprintf(stderr, "Malformed base64 encoding\n");
        return 4;
    }

    CHashWriter ss(0);
    ss << strMessageMagic;
    ss << strMessage;

    CKey key;
    if (!key.SetCompactSignature(ss.GetHash(), vchSig)) {
        fprintf(stderr, "Error reading signature\n");
        return 5;
    }

    // 0 is "success" in standard UNIX return codes
    if (key.GetPubKey().GetID() == keyID) {
        //printf("pass\n");
        return 0;
    } else {
        //printf("fail\n");
        return 1;
    }
}


#endif
