#ifndef _COMMAND_H
#define _COMMAND_H

#include "zncconfig.h"
#include "Utils.h"

class CModule;

class CCommand {
public:
	/// Type for the callback function that handles the actual command.
	typedef void (Class::*CmdFunc)(const CString& sLine);

	/// Default constructor, needed so that this can be saved in a std::map.
	CCommand();

	/** Construct a new CCommand.
	 * @param sCmd The name of the command.
	 * @param func The command's callback function.
	 * @param sArgs Help text describing the arguments to this command.
	 * @param sDesc Help text describing what this command does.
	 */
	CCommand(const CString& sCmd, Class* pObject, ModCmdFunc func, const CString& sArgs, const CString& sDesc);

	/** Copy constructor, needed so that this can be saved in a std::map.
	 * @param other Object to copy from.
	 */
	CCommand(const CCommand& other);

	/** Assignment operator, needed so that this can be saved in a std::map.
	 * @param other Object to copy from.
	 */
	CCommand& operator=(const CCommand& other);

	/** Initialize a CTable so that it can be used with AddHelp().
	 * @param Table The instance of CTable to initialize.
	 */
	static void InitHelp(CTable& Table);

	/** Add this command to the CTable instance.
	 * @param Table Instance of CTable to which this should be added.
	 * @warning The Table should be initialized via InitHelp().
	 */
	void AddHelp(CTable& Table) const;

	const CString& GetCommand() const { return m_sCmd; }
	CmdFunc GetFunction() const { return m_pFunc; }
	const CString& GetArgs() const { return m_sArgs; }
	const CString& GetDescription() const { return m_sDesc; }

	void Call(const CString& sLine) const { (m_pObject->*m_pFunc)(sLine); }

private:
	CString m_sCmd;
	Class *m_pObject;
	ModCmdFunc m_pFunc;
	CString m_sArgs;
	CString m_sDesc;
};

class CCommands : public map<CString, CCommand> {
public:
	/// @return True if the command was successfully added.
	bool AddCommand(const CCommand& Command);

	/// @return True if the command was successfully removed.
	bool RemCommand(const CString& sCmd);

	/// @return The CCommand instance or NULL if none was found.
	const CCommand* FindCommand(const CString& sCmd) const;
};
#endif // !_COMMAND_H
