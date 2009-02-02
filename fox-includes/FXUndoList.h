/********************************************************************************
*                                                                               *
*                  U n d o / R e d o - a b l e   C o m m a n d                  *
*                                                                               *
*********************************************************************************
* Copyright (C) 2000,2006 by Jeroen van der Zijp.   All Rights Reserved.        *
*********************************************************************************
* This library is free software; you can redistribute it and/or                 *
* modify it under the terms of the GNU Lesser General Public                    *
* License as published by the Free Software Foundation; either                  *
* version 2.1 of the License, or (at your option) any later version.            *
*                                                                               *
* This library is distributed in the hope that it will be useful,               *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU             *
* Lesser General Public License for more details.                               *
*                                                                               *
* You should have received a copy of the GNU Lesser General Public              *
* License along with this library; if not, write to the Free Software           *
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.    *
*********************************************************************************
* $Id: FXUndoList.h 2346 2006-02-14 03:26:11Z lyle $                        *
********************************************************************************/
#ifndef FXUNDOLIST_H
#define FXUNDOLIST_H

#ifndef FXOBJECT_H
#include "FXObject.h"
#endif

namespace FX {


class FXUndoList;
class FXCommandGroup;


/**
* Base class for undoable commands.  Each undo records all the
* information necessary to undo as well as redo a given operation.
* Since commands are derived from FXObject, subclassed commands can
* both send and receive messages (like ID_GETINTVALUE, for example).
*/
class FXAPI FXCommand : public FXObject {
  FXDECLARE_ABSTRACT(FXCommand)
  friend class FXUndoList;
  friend class FXCommandGroup;
private:
  FXCommand *next;
private:
  FXCommand(const FXCommand&);
  FXCommand &operator=(const FXCommand&);
protected:
  FXCommand():next(NULL){}
public:

  /**
  * Undo this command; this should save the
  * information for a subsequent redo.
  */
  virtual void undo() = 0;

  /**
  * Redo this command; this should save the
  * information for a subsequent undo.
  */
  virtual void redo() = 0;

  /**
  * Return the size of the information in the undo record.
  * The undo list may be trimmed to limit memory usage to
  * a certain limit.  The value returned should include
  * the size of the command record itself as well as any
  * data linked from it.
  */
  virtual FXuint size() const;

  /**
  * Name of the undo command to be shown on a button;
  * for example, "Undo Delete".
  */
  virtual FXString undoName() const;

  /**
  * Name of the redo command to be shown on a button;
  * for example, "Redo Delete".
  */
  virtual FXString redoName() const;

  /**
  * Return TRUE if this command can be merged with previous undo
  * commands.  This is useful to combine e.g. multiple consecutive
  * single-character text changes into a single block change.
  * The default implementation returns FALSE.
  */
  virtual bool canMerge() const;

  /**
  * Called by the undo system to try and merge the new incoming command
  * with this command; should return TRUE if merging was possible.
  * The default implementation returns FALSE.
  */
  virtual bool mergeWith(FXCommand* command);

  /// Delete undo command
  virtual ~FXCommand(){}
  };



/**
* Group of undoable commands.  A group may comprise multiple
* individual actions which together undo (or redo) a larger
* operation.  Even larger operations may be built by nesting
* multiple undo groups.
*/
class FXAPI FXCommandGroup : public FXCommand {
  FXDECLARE(FXCommandGroup)
  friend class FXUndoList;
private:
  FXCommand      *undolist;
  FXCommand      *redolist;
  FXCommandGroup *group;
private:
  FXCommandGroup(const FXCommandGroup&);
  FXCommandGroup &operator=(const FXCommandGroup&);
public:

  /// Construct initially empty undo command group
  FXCommandGroup():undolist(NULL),redolist(NULL),group(NULL){}

  /// Return TRUE if empty
  bool empty(){ return !undolist; }

  /// Undo whole command group
  virtual void undo();

  /// Redo whole command group
  virtual void redo();

  /// Return the size of the command group
  virtual FXuint size() const;

  /// Delete undo command and sub-commands
  virtual ~FXCommandGroup();
  };



/**
* The Undo List class manages a list of undoable commands.
*/
class FXAPI FXUndoList : public FXCommandGroup {
  FXDECLARE(FXUndoList)
private:
  FXint      undocount;     // Number of undo records
  FXint      redocount;     // Number of redo records
  FXint      marker;        // Marker value
  FXuint     space;         // Space taken up by all the undo records
  bool       working;       // Currently busy with undo or redo
private:
  FXUndoList(const FXUndoList&);
  FXUndoList &operator=(const FXUndoList&);
public:
  long onCmdUndo(FXObject*,FXSelector,void*);
  long onUpdUndo(FXObject*,FXSelector,void*);
  long onCmdRedo(FXObject*,FXSelector,void*);
  long onUpdRedo(FXObject*,FXSelector,void*);
  long onCmdClear(FXObject*,FXSelector,void*);
  long onUpdClear(FXObject*,FXSelector,void*);
  long onCmdRevert(FXObject*,FXSelector,void*);
  long onUpdRevert(FXObject*,FXSelector,void*);
  long onCmdUndoAll(FXObject*,FXSelector,void*);
  long onCmdRedoAll(FXObject*,FXSelector,void*);
  long onUpdUndoCount(FXObject*,FXSelector,void*);
  long onUpdRedoCount(FXObject*,FXSelector,void*);
public:
  enum{
    ID_CLEAR=FXWindow::ID_LAST,
    ID_REVERT,
    ID_UNDO,
    ID_REDO,
    ID_UNDO_ALL,
    ID_REDO_ALL,
    ID_UNDO_COUNT,
    ID_REDO_COUNT,
    ID_LAST
    };
public:

  /**
  * Make new empty undo list, initially unmarked.
  */
  FXUndoList();

  /**
  * Cut the redo list.
  * This is automatically invoked when a new undo command is added.
  */
  void cut();

  /**
  * Add new command, executing it if desired. The new command will be merged
  * with the previous command if merge is TRUE and we're not at a marked position
  * and the commands are mergeable.  Otherwise the new command will be appended
  * after the last undo command in the currently active undo group.
  * If the new command is successfully merged, it will be deleted.  Furthermore,
  * all redo commands will be deleted since it is no longer possible to redo
  * from this point.
  */
  void add(FXCommand* command,bool doit=false,bool merge=true);

  /**
  * Begin undo command sub-group. This begins a new group of commands that
  * are treated as a single command.  Must eventually be followed by a
  * matching end() after recording the sub-commands.  The new sub-group
  * will be appended to its parent group's undo list when end() is called.
  */
  void begin(FXCommandGroup *command);

  /**
  * End undo command sub-group.  If the sub-group is still empty, it will
  * be deleted; otherwise, the sub-group will be added as a new command
  * into parent group.
  * A matching begin() must have been called previously.
  */
  void end();

  /**
  * Abort the current command sub-group being compiled.  All commands
  * already added to the sub-groups undo list will be discarded.
  * Intermediate command groups will be left intact.
  */
  void abort();

  /**
  * Undo last command. This will move the command to the redo list.
  */
  virtual void undo();

  /**
  * Redo next command. This will move the command back to the undo list.
  */
  virtual void redo();

  /// Undo all commands
  void undoAll();

  /// Redo all commands
  void redoAll();

  /// Revert to marked
  void revert();

  /// Can we undo more commands
  bool canUndo() const;

  /// Can we redo more commands
  bool canRedo() const;

  /// Can revert to marked
  bool canRevert() const;

  /**
  * Return TRUE if currently inside undo or redo operation; this
  * is useful to avoid generating another undo command while inside
  * an undo operation.
  */
  bool busy() const { return working; }

  /// Current top level undo command
  FXCommand* current() const { return undolist; }

  /**
  * Return name of the first undo command available; if no
  * undo command available this will return the empty string.
  */
  virtual FXString undoName() const;

  /**
  * Return name of the first redo command available; if no
  * Redo command available this will return the empty string.
  */
  virtual FXString redoName() const;

  /// Number of undo records
  FXint undoCount() const { return undocount; }

  /// Number of redo records
  FXint redoCount() const { return redocount; }

  /// Size of undo information
  virtual FXuint size() const;

  /**
  * Clear list, and unmark all states.
  * All undo and redo information will be destroyed.
  */
  void clear();

  /**
  * Trim undo list down to at most nc commands.
  * Call this periodically to prevent the undo-list from growing
  * beyond a certain number of records.
  */
  void trimCount(FXint nc);

  /**
  * Trim undo list down to at most size sz.
  * Call this periodically to prevent the undo-list from growing
  * beyond a certain amount of memory.
  */
  void trimSize(FXuint sz);

  /**
  * Mark the current state of the undo list, which is initially unmarked.
  * There can be only one active mark at any time.  Call mark() at any
  * time when you know the document to be "clean"; for example when you
  * save the document to disk.
  */
  void mark();

  /**
  * Unmark all states in the undo list.
  */
  void unmark();

  /**
  * Check if the current state was marked, if the application has returned
  * to the previously marked state.
  */
  bool marked() const;
  };


}

#endif
