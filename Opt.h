#ifndef __OPT_H__
#define __OPT_H__

/// @file Opt.h
///
/// Declare Opt classes for walk actions
///
#include "codes.h"

/// Base class for optimizing walk actions.

class Opt{
  protected:
  int action_array[2][NUM_NODE_TYPES+1];
  OptType type;
  Opt(OptType _type) : type(_type) {}
  public:

  /// Key method of Opt: given a opening decision, and a node, return
  /// an action to perform.  The action will depend on the type of
  /// node considered and which walk is being done.

  int action(int openDecision, Tree::GenericTreeNode *node){
    return action_array[openDecision][node->getType()];
  }
  OptType getSelfType() {return type;}
};

/// Class for optimizing remote gravity walk actions.
class RemoteOpt : public Opt{
  public:
  RemoteOpt() : Opt(Remote){
    // don't need to open
    //
    // local data
    action_array[0][Tree::Bucket] = DUMP;
    action_array[0][Tree::Internal] = DUMP;
    /*
    action_array[0][Boundary] = COMPUTE;
    action_array[0][NonLocal] = COMPUTE;
    action_array[0][NonLocalBucket] = COMPUTE;
    action_array[0][Cached] = COMPUTE;
    action_array[0][CachedBucket] = COMPUTE;
    */
    action_array[0][Tree::Boundary] = DUMP;
    // XXX - changed to COMPUTE from DUMP. see below also
    action_array[0][Tree::NonLocal] = COMPUTE;
    action_array[0][Tree::NonLocalBucket] = DUMP;
    
    // changed these two to COMPUTE from DEFER
    action_array[0][Tree::Cached] = COMPUTE;
    action_array[0][Tree::CachedBucket] = COMPUTE;

    action_array[0][Tree::CachedEmpty] = DUMP;

    action_array[0][Tree::Empty] = DUMP;
    action_array[0][Tree::Top] = ERROR;
    action_array[0][Tree::Invalid] = ERROR;
     
    // need to open
    //
    // local data
    action_array[1][Tree::Internal] = DUMP;
    action_array[1][Tree::Bucket] = DUMP;
    
    // non-local data
    action_array[1][Tree::NonLocal] = KEEP;
    action_array[1][Tree::NonLocalBucket] = KEEP_REMOTE_BUCKET;
    action_array[1][Tree::Boundary] = KEEP;

    action_array[1][Tree::Cached] = KEEP;
    action_array[1][Tree::CachedBucket] = KEEP_REMOTE_BUCKET;

    // in this case, ancestors of CachedEmpty nodes must be checked as well
    action_array[1][Tree::CachedEmpty] = DUMP;

    action_array[1][Tree::Top] = ERROR;
    action_array[1][Tree::Invalid] = ERROR;
    action_array[1][Tree::Empty] = DUMP;

  }

};

/// Class for optimizing local gravity walk actions.
class LocalOpt : public Opt{
  public:
  LocalOpt() : Opt(Local){
    // don't need to open
    // these nodes are your concern
    action_array[0][Tree::Internal] = COMPUTE;
    action_array[0][Tree::Bucket] = COMPUTE;

    action_array[0][Tree::Boundary] = COMPUTE;
    // XXX - changed to DUMP from COMPUTE
    action_array[0][Tree::NonLocal] = DUMP;
    action_array[0][Tree::NonLocalBucket] = COMPUTE;
    // changed these to DUMP from COMPUTE - remote does computation now
    action_array[0][Tree::Cached] = DUMP;
    action_array[0][Tree::CachedBucket] = DUMP;

    // these nodes are no one's concern
    action_array[0][Tree::Empty] = DUMP;
    action_array[0][Tree::CachedEmpty] = DUMP;
    action_array[0][Tree::Top] = ERROR;
    action_array[0][Tree::Invalid] = ERROR;
    //--------------
    // need to open node
    // local data
    action_array[1][Tree::Internal] = KEEP;
    action_array[1][Tree::Bucket] = KEEP_LOCAL_BUCKET;
    action_array[1][Tree::Boundary] = KEEP;

    // remote data
    action_array[1][Tree::NonLocal] = DUMP;
    action_array[1][Tree::NonLocalBucket] = DUMP;
    // remote opt KEEPs Cached and KEEP_REMOTE_BUCKETs CachedBucket
    action_array[1][Tree::CachedBucket] = DUMP;
    action_array[1][Tree::Cached] = DUMP;

    // discard
    action_array[1][Tree::Empty] = DUMP;
    action_array[1][Tree::CachedEmpty] = DUMP;
    action_array[1][Tree::Top] = ERROR;
    action_array[1][Tree::Invalid] = ERROR;
  }
  
};

/// Class for optimizing experimental "push" gravity walk actions.

class PushGravityOpt : public Opt{
  public:
  PushGravityOpt() : Opt(PushGravity){
    // don't need to open node
    // these nodes are your concern
    action_array[0][Tree::Internal] = COMPUTE;
    action_array[0][Tree::Bucket] = COMPUTE;

    action_array[0][Tree::Boundary] = KEEP;
    // XXX - changed to DUMP from COMPUTE
    action_array[0][Tree::NonLocal] = DUMP;
    action_array[0][Tree::NonLocalBucket] = DUMP;
    // changed these to DUMP from COMPUTE - remote does computation now
    action_array[0][Tree::Cached] = DUMP;
    action_array[0][Tree::CachedBucket] = DUMP;

    // these nodes are no one's concern
    action_array[0][Tree::Empty] = DUMP;
    action_array[0][Tree::CachedEmpty] = DUMP;
    action_array[0][Tree::Top] = ERROR;
    action_array[0][Tree::Invalid] = ERROR;
    //--------------
    // need to open node
    // local data
    action_array[1][Tree::Internal] = KEEP;
    action_array[1][Tree::Bucket] = KEEP_LOCAL_BUCKET;
    action_array[1][Tree::Boundary] = KEEP;

    // remote data
    action_array[1][Tree::NonLocal] = DUMP;
    action_array[1][Tree::NonLocalBucket] = DUMP;
    // remote opt KEEPs Cached and KEEP_REMOTE_BUCKETs CachedBucket
    action_array[1][Tree::CachedBucket] = DUMP;
    action_array[1][Tree::Cached] = DUMP;

    // discard
    action_array[1][Tree::Empty] = DUMP;
    action_array[1][Tree::CachedEmpty] = DUMP;
    action_array[1][Tree::Top] = ERROR;
    action_array[1][Tree::Invalid] = ERROR;
  }
  
};

/// Optimization for Prefetch walk.

class PrefetchOpt : public Opt{
  public: 
  PrefetchOpt() : Opt(Pref){
    for(int i = 1; i <= NUM_NODE_TYPES; i++) 
      action_array[0][i] = DUMP;
    action_array[0][Tree::Invalid] = ERROR;
    action_array[0][Tree::Top] = ERROR;

    action_array[1][Tree::Internal] = DUMP;
    action_array[1][Tree::Bucket] = DUMP;

    action_array[1][Tree::Boundary] = KEEP;
    // we KEEP NonLocal nodes, even though we don't have their
    // children - the tw object will request the children if need be
    action_array[1][Tree::NonLocal] = KEEP;
    action_array[1][Tree::NonLocalBucket] = KEEP_REMOTE_BUCKET;
    action_array[1][Tree::Cached] = KEEP;
    action_array[1][Tree::CachedBucket] = KEEP_REMOTE_BUCKET;

    action_array[1][Tree::CachedEmpty] = DUMP;
    action_array[1][Tree::Empty] = DUMP;
    action_array[1][Tree::Invalid] = ERROR; // node not properly initialized
    action_array[1][Tree::Top] = ERROR;    // not handled anywhere in the original code, so ERROR
  }
};
#endif
