
/*
 * Copyright (c) 2011 Novell, Inc.
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#ifndef SNAPSHOT_H
#define SNAPSHOT_H


#include <vector>


namespace snapper
{
    using namespace std;


    enum SnapshotType { SINGLE, PRE, POST };


    class Snapshot
    {
    public:

	Snapshot() : type(SINGLE), num(0), pre_num(0) {}

	SnapshotType type;

	unsigned int num;

	string date;

	string description;	// empty for type=POST

	unsigned int pre_num;	// valid only for type=POST

	string baseDir() const;
	string snapshotDir() const;

	bool writeInfo() const;
	bool createFilesystemSnapshot() const;

    };


    std::ostream& operator<<(std::ostream& s, const Snapshot& x);


    inline bool operator<(const Snapshot& a, const Snapshot& b)
    {
	return a.num < b.num;
    }


    extern vector<Snapshot>::const_iterator snapshot1;
    extern vector<Snapshot>::const_iterator snapshot2;


    class Snapshotlist
    {
    public:

	Snapshotlist() : initialized(false) {}

	void assertInit();

	vector<Snapshot>::const_iterator begin() const { return snapshots.begin(); }
	vector<Snapshot>::const_iterator end() const { return snapshots.end(); }

	vector<Snapshot>::iterator find(unsigned int num);
	vector<Snapshot>::const_iterator find(unsigned int num) const;

	unsigned int createSingleSnapshot(string description);
	unsigned int createPreSnapshot(string description);
	unsigned int createPostSnapshot(unsigned int pre_num);

    private:

	void initialize();

	void read();

	unsigned int nextNumber();

	bool initialized;

	vector<Snapshot> snapshots;

    };


    extern Snapshotlist snapshotlist;

}


#endif