// Copyright (c) 2017 The Sucrecoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SUCRECOIN_ASSETDB_H
#define SUCRECOIN_ASSETDB_H

#include "fs.h"
#include "serialize.h"

#include <string>
#include <map>
#include <dbwrapper.h>

class CNewAsset;
class uint256;
class COutPoint;

/** Access to the block database (blocks/index/) */
class CAssetsDB : public CDBWrapper
{
public:
    explicit CAssetsDB(size_t nCacheSize, bool fMemory = false, bool fWipe = false);

    CAssetsDB(const CAssetsDB&) = delete;
    CAssetsDB& operator=(const CAssetsDB&) = delete;

    // Write to database functions
    bool WriteAssetData(const CNewAsset& asset);
    bool WriteMyAssetsData(const std::string &strName, const std::set<COutPoint>& setOuts);
    bool WriteAssetAddressQuantity(const std::string& assetName, const std::string& address, const CAmount& quantity);
    bool WriteBlockUndoAssetData(const uint256& blockhash, const std::vector<std::pair<std::string, std::string> >& vIPFSHashes);

    // Read from database functions
    bool ReadAssetData(const std::string& strName, CNewAsset& asset);
    bool ReadMyAssetsData(const std::string &strName, std::set<COutPoint>& setOuts);
    bool ReadAssetAddressQuantity(const std::string& assetName, const std::string& address, CAmount& quantity);
    bool ReadBlockUndoAssetData(const uint256& blockhash, std::vector<std::pair<std::string, std::string> >& vIPFSHashes);

    // Erase from database functions
    bool EraseAssetData(const std::string& assetName);
    bool EraseMyAssetData(const std::string& assetName);
    bool EraseAssetAddressQuantity(const std::string &assetName, const std::string &address);

    // Helper functions
    bool EraseMyOutPoints(const std::string& assetName);
    bool LoadAssets();
    bool AssetDir(std::vector<CNewAsset>& assets, const std::string filter, const size_t count, const long start);
    bool AssetDir(std::vector<CNewAsset>& assets);
};


#endif //SUCRECOIN_ASSETDB_H
