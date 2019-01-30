/*
 * Hydrogen
 * Copyright(c) 2002-2008 by Alex >Comix< Cominu [comix@users.sourceforge.net]
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


#ifndef EXPORT_MIDI_DIALOG_H
#define EXPORT_MIDI_DIALOG_H


#include "ui_ExportMidiDialog_UI.h"
#include <hydrogen/object.h>

namespace H2Core {
	class Instrument;
}

///
/// Dialog for exporting song to midi
///
class ExportMidiDialog : public QDialog, public Ui_ExportMidiDialog_UI, public H2Core::Object
{
	H2_OBJECT
	Q_OBJECT

	public:
		ExportMidiDialog(QWidget* parent);
	~ExportMidiDialog();

private slots:
	void on_browseBtn_clicked();
	void on_closeBtn_clicked();
	void on_okBtn_clicked();
	void on_exportNameTxt_textChanged(const QString& text);

private:
	void exportTrack();
	bool m_bFileSelected;
	QString m_sExtension;
};


#endif

