/*
 *					AspireCore
 * Copyright (C) 2008 AspireDev <http://www.aspiredev.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef AspireMessageHandler_H
#define Aspire_MessageHanlder_H

class AspireMessageHandler //: public EventableObject // incase i decided to expand this
{
	public:
		~AspireMessageHandler();
		static AspireMessageHandler &GetInst(); // Use this anytime you need to call the class

		// Database Interaction
		void MasterDatabaseLoad(); // Loads all databases
		void LoadKickMessages(); // Loads kick messages from the database
		bool AddKickMessage(std::string &Index, std::string &Message); // Adds a predefine kick message
		bool RemoveKickMessage(std::string &Index); // Removes a predefined kick message

		std::string IsPreDefined(std::string &Index); // Checks if the Index has a pre-defined message and returns the message if so

		// Config related
		bool IsEnabled() 
		{
			return sWorld.EnablePreDefinedKicks;
		}

		uint32 SendPreDefinedKickList(Player *Plr, const char *Substring = ""); // Sending a list of pre-defined kicks to the player

	private:
		AspireMessageHandler();

	protected:

		// Mutexes
		Mutex kMessageLock;

		// Pointers
		static AspireMessageHandler *Inst;

		// Storage Containers
		map<std::string, std::string> KickMsgs;
};


#define AspireMsgHandler AspireMessageHandler::GetInst()

#endif // AspireMessageHandler_H