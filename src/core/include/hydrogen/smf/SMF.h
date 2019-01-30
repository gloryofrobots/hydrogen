/*
 * Hydrogen
 * Copyright(c) 2002-2004 by Alex >Comix< Cominu [comix@users.sourceforge.net]
 *
 * http://www.hydrogen-music.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef SMF_H
#define SMF_H

#include <hydrogen/object.h>
#include <hydrogen/basics/song.h>

#include <string>
#include <cstdio>
#include <vector>

#include <hydrogen/smf/SMFEvent.h>

namespace H2Core
{

class SMFHeader : public SMFBase, public H2Core::Object
{
	H2_OBJECT
public:
	SMFHeader( int nFormat, int nTracks, int nTPQN );
	~SMFHeader();

	int m_nFormat;		///< SMF format
	int m_nTracks;		///< number of tracks
	int m_nTPQN;		///< ticks per quarter note

	virtual std::vector<char> getBuffer();
};



class SMFTrack : public SMFBase, public H2Core::Object
{
	H2_OBJECT
public:

	SMFTrack();
	~SMFTrack();

	void addEvent( SMFEvent *pEvent );

	virtual std::vector<char> getBuffer();

private:
	std::vector<SMFEvent*> m_eventList;
};



class SMF : public SMFBase, public H2Core::Object
{
	H2_OBJECT
public:
	SMF();
	~SMF();

	void addTrack( SMFTrack *pTrack );
	virtual std::vector<char> getBuffer();

private:
	std::vector<SMFTrack*> m_trackList;

	SMFHeader* m_pHeader;

};


typedef std::vector<SMFEvent*> EventList;

class SMFWriter : public H2Core::Object
{
	H2_OBJECT
public:
	SMFWriter(const char* sWriterName);
	virtual ~SMFWriter();

	void save( const QString& sFilename, Song *pSong );

protected:
	void sortEvents(EventList* pEventList);
	virtual void prepareEvents(Song* pSong,  SMF& smf )=0;
	virtual void  packEvents(Song* pSong,  SMF& smf) = 0;
	virtual EventList* getEvents(Song* pSong,  Instrument* pInstr) = 0;
private:
    void saveSMF( const QString& sFilename,  SMF& smf );
    FILE *m_file;

};

class SMFWriterSingle : public SMFWriter
{
    H2_OBJECT
public:
    SMFWriterSingle();
	virtual ~SMFWriterSingle();
protected:
	virtual void prepareEvents(Song* pSong,  SMF& smf );
	virtual void  packEvents(Song* pSong,  SMF& smf) ;
	virtual EventList* getEvents(Song* pSong,  Instrument* pInstr) ;
private:
	EventList m_eventList;
};


class SMFWriterMulti : public SMFWriter
{
    H2_OBJECT
public:
    SMFWriterMulti();
	virtual ~SMFWriterMulti();
protected:
	virtual void prepareEvents(Song* pSong,  SMF& smf );
	virtual void  packEvents(Song* pSong,  SMF& smf) ;
	virtual EventList* getEvents(Song* pSong,  Instrument* pInstr) ;
private:
	// contains events for each instrument in separate vector
	std::vector<EventList*> m_eventLists;
};

};

#endif

