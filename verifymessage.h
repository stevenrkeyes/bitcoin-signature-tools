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
        return false;
    }

    CKeyID keyID;
    if (!addr.GetKeyID(keyID)) {
        fprintf(stderr, "Address does not refer to key\n");
        return false;
    }

    bool fInvalid = false;
    vector<unsigned char> vchSig = DecodeBase64(strSign.c_str(), &fInvalid);

    if (fInvalid) {
        fprintf(stderr, "Malformed base64 encoding\n");
        return false;
    }

    CHashWriter ss(0);
    ss << strMessageMagic;
    ss << strMessage;

    CKey key;
    if (!key.SetCompactSignature(ss.GetHash(), vchSig)) {
        fprintf(stderr, "Error reading signature\n");
        return false;
    }

    // 0 is "success" in standard UNIX return codes
    if (key.GetPubKey().GetID() == keyID) {
        //printf("pass\n");
        return true;
    } else {
        //printf("fail\n");
        return false;
    }
}


#endif
