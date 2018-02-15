//------------------------------------------------------------------------------
#include<vcl.h>
#pragma hdrstop
#include "FileInfo.h"
//------------------------------------------------------------------------------
#pragma package(smart_init)

//------------------------------------------------------------------------------
String TFileInfo::Table       ("T_FILES");
String TFileInfo::FldID       ("FILE_ID");
String TFileInfo::FldDatasetID("DATASET_ID");
String TFileInfo::FldSize     ("SIZE");
String TFileInfo::FldFileName ("FILE_NAME");
String TFileInfo::FldComment  ("COMMENT");
//------------------------------------------------------------------------------
__fastcall TFileInfo::TFileInfo ()
{
	Clear();
}
//------------------------------------------------------------------------------
__fastcall TFileInfo::TFileInfo (const TFileInfo &other)
{
	AssignAll (other);
}
//------------------------------------------------------------------------------
TFileInfo __fastcall TFileInfo::operator= (const TFileInfo &other)
{
	AssignAll (other);
	return (*this);
}
//------------------------------------------------------------------------------
void __fastcall TFileInfo::AssignAll (const TFileInfo &other)
{
	FileID    = other.FileID;
	DatasetID = other.DatasetID;
	Size      = other.Size;
	FileName  = other.FileName;
	Comment   = other.Comment;
}
//------------------------------------------------------------------------------
void __fastcall TFileInfo::Clear ()
{
	FileID    = 0;
	DatasetID = 0;
	Size      = 0;
	FileName  = "";
	Comment   = "";
}
//------------------------------------------------------------------------------
bool __fastcall TFileInfo::operator== (const TFileInfo &other) const
{
	if (FileID    != other.FileID)
		return (false);
	if (DatasetID != other.DatasetID)
		return (false);
	if (Size      != other.Size)
		return (false);
	if (FileName  != other.FileName)
		return (false);
	if (Comment   != other.Comment)
		return (false);
	return (true);
}
//------------------------------------------------------------------------------
void __fastcall TFileInfo::SetFileID (const int value)
{
	m_nFileID = value;
}
//------------------------------------------------------------------------------
int __fastcall TFileInfo::GetFileID () const
{
	return (m_nFileID);
}
//------------------------------------------------------------------------------
void __fastcall TFileInfo::SetDatasetID (const int value)
{
	m_nDatasetID = value;
}
//------------------------------------------------------------------------------
int __fastcall TFileInfo::GetDatasetID () const
{
	return (m_nDatasetID);
}
//------------------------------------------------------------------------------
void __fastcall TFileInfo::SetSize (const int value)
{
	m_nSize = value;
}
//------------------------------------------------------------------------------
int __fastcall TFileInfo::GetSize () const
{
	return (m_nSize);
}
//------------------------------------------------------------------------------
void __fastcall TFileInfo::SetFileName (const String &value)
{
	m_strFileName = value;
}
//------------------------------------------------------------------------------
String __fastcall TFileInfo::GetFileName () const
{
	return (m_strFileName);
}
//------------------------------------------------------------------------------
void __fastcall TFileInfo::SetComment (const String &value)
{
	m_strComment = value;
}
//------------------------------------------------------------------------------
String __fastcall TFileInfo::GetComment () const
{
	return (m_strComment);
}
//------------------------------------------------------------------------------
bool __fastcall TFileInfo::LoadFromDB (TADOQuery *query)
{
	bool f = true;
	
	try {
		FileID =    query->Fields->FieldByName (FldID)->AsInteger;
		DatasetID = query->Fields->FieldByName (FldDatasetID)->AsInteger;
		Size =      query->Fields->FieldByName (FldSize)->AsInteger;
		FileName =  query->Fields->FieldByName (FldFileName)->AsString;
		Comment =   query->Fields->FieldByName (FldComment)->AsString;
	}
	catch (...) {
		f = false;
	}
	return (f);;
}
//------------------------------------------------------------------------------
bool __fastcall TFileInfo::InsertAsNew (TADOQuery *query, String &strErr)
{
	int id;
	bool f;
	String strSql;
	
	f = GetFieldMax (query, Table, FldID, id);
	if (f) {
		strSql = "insert into " + Table + "(" + FldID + ") values (" + String (id + 1) + ");";
		f = RunQuery (query, strSql, QueryExec, strErr);
	}
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TFileInfo::InsertAsNew (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = InsertAsNew(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TFileInfo::UpdateInDB (TADOQuery *query, String &strErr)
{
	String strSql;
	bool f;
	
	strSql = "update " + Table + "set "  + ModifyForUpdate(FldID, FileID) + ", " + 
				ModifyForUpdate(FldDatasetID, DatasetID) + ", " + 
				ModifyForUpdate(FldSize, Size) + ", " + 
				ModifyForUpdate(FldFileName, FileName) + ", " + 
				ModifyForUpdate(FldComment, Comment) + 
			"where " + FldID + " = " + String(FileID);
	f = RunQuery(query, strSql, QueryExec, strErr);
	return (f);
}
//------------------------------------------------------------------------------
bool __fastcall TFileInfo::UpdateInDB (TADOConnection *db, String &strErr)
{
	bool f;
	TADOQuery *query = InitQuery (db, NULL);
	
	f = UpdateInDB(query, strErr);
	delete query;
	return (f);
}
//------------------------------------------------------------------------------
