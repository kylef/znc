#include "Command.h"
#include "Utils.h"

CCommand::CCommand()
	: m_sCmd(), m_pObject(NULL), m_pFunc(NULL), m_sArgs(), m_sDesc() {}

CCommand::CCommand(const CString& sCmd, Class* pObject, ModCmdFunc func, const CString& sArgs, const CString& sDesc)
	: m_sCmd(sCmd), m_pObject(pObject), m_pFunc(func), m_sArgs(sArgs), m_sDesc(sDesc) {}

CCommand::CCommand(const CCommand& other)
	: m_sCmd(other.m_sCmd), m_pObject(other.m_pObject), m_pFunc(other.m_pFunc), m_sArgs(other.m_sArgs), m_sDesc(other.m_sDesc) {}


CCommand& CCommand::operator=(const CCommand& other) {
	m_sCmd = other.m_sCmd;
	m_pFunc = other.m_pFunc;
	m_sArgs = other.m_sArgs;
	m_sDesc = other.m_sDesc;
	return *this;
}

void CCommand::InitHelp(CTable& Table) {
	Table.AddColumn("Command");
	Table.AddColumn("Arguments");
	Table.AddColumn("Description");
}

void CCommand::AddHelp(CTable& Table) const {
	Table.AddRow();
	Table.SetCell("Command", GetCommand());
	Table.SetCell("Arguments", GetArgs());
	Table.SetCell("Description", GetDescription());
}

bool CCommands::AddCommand(const CCommand& Command) {
	if (Command.GetFunction() == NULL)
		return false;
	if (Command.GetCommand().find(' ') != CString::npos)
		return false;
	if (FindCommand(Command.GetCommand()) != NULL)
		return false;

	(*this)[Command.GetCommand()] = Command;
	return true;
}

bool CCommands::RemCommand(const CString& sCmd) {
	return erase(sCmd) > 0;
}

const CCommand* CCommands::FindCommand(const CString& sCmd) const {
	for (CCommands::const_iterator it = begin(); it != end(); ++it) {
		if (!it->first.Equals(sCmd))
			continue;
		return &it->second;
	}
	return NULL;
}

