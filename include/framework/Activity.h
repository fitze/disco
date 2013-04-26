// Modified by Chris Dembia (2013).

#ifndef FRAMEWORK_ACTIVITY_H
#define FRAMEWORK_ACTIVITY_H

#include <string>

#include "framework/PtrInterface.h"
#include "framework/Nominal.h"
#include "framework/BaseNotifiee.h"

using std::string;

namespace framework
{

class Activity : public PtrInterface<Activity> {
public:

    typedef Ptr<Activity> Ptr;

    /* Notifiee class for Activities */
    class Notifiee : public BaseNotifiee<Activity> {
    public:
        typedef Ptr<Notifiee> Ptr;
        Notifiee(Activity * act) : BaseNotifiee<Activity>(act) { }
        virtual void onNextExecutionTimeIs() { }
        virtual void onStatusIs() { } 
    };

    class Manager;

    enum Status {
        _free,
        _waiting,
        _ready,
        _executing,
        _scheduled,
        _deleted
    };
    static inline Status free() { return _free; }
    static inline Status waiting() { return _waiting; }
    static inline Status ready() { return _ready; }
    static inline Status executing() { return _executing; }
    static inline Status scheduled() { return _scheduled; }
    static inline Status deleted() { return _deleted; }

    virtual Status status() const = 0;
    virtual void statusIs(Status s)  = 0;

    virtual Duration nextExecutionTime() const = 0;
    virtual void nextExecutionTimeIs(Duration time) = 0;
    virtual void nextExecutionTimeInc(Duration time) = 0;

    virtual Ptr<Notifiee> notifiee() const = 0;

    virtual void notifieeIs(Notifiee* n) = 0;

    virtual string name() const { return name_; }

protected:

    Activity(const string& name) : name_(name) { }

private:

    string name_;

};

class Activity::Manager : public PtrInterface<Activity::Manager> {
public:

    typedef Ptr<Activity::Manager> Ptr;

    virtual Ptr<Activity> activityNew(const string &name) = 0;
    virtual Ptr<Activity> activity(const string &name) const = 0;
    virtual Activity::Ptr activityDel(const string &name) = 0;

    virtual Duration timePassed() const = 0;
    virtual void timePassedIs(Duration time) = 0;
    virtual void timePassedInc(Duration time) = 0;

    virtual void activityAtBackIs(Activity::Ptr) = 0;

    virtual void activityFlush() = 0;

private:

    /* Up to you */
    // TODO

};

} // namespace framework

#endif
