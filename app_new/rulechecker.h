#include <boost/shared_ptr.hpp>
#include <QtGui>
#include <QtSql>
#include <QHash>
#include <QtTest/QtTest>

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

using namespace boost;

////////////////////////////////////////////////////////////////////////
#ifndef RULECHECKER_H
#define RULECHECKER_H

static const char *strEnable = 
     QT_TRANSLATE_NOOP("RULE", "ENABLE");/**< Keyword that Triggers the *enabling* of a widget, inside a rule */

static const char *strDisable = 
     QT_TRANSLATE_NOOP("RULE", "DISABLE");/**< Keyword that Triggers the *disabling* of a widget, inside a rule */

static const char *strNothing = 
     QT_TRANSLATE_NOOP("RULE", "NOTHING");/**< Keyword that allows a rule to not touch the user interface */

static const char *StrRulePtr = 
     QT_TRANSLATE_NOOP("RULE", "ptr");/**< Keyword for calling a reference value on [UI_Rule_Ptrs] */

//! cell struct
/*! This structure references a cell (field index, form, mapper index), and optionally a linked cell that origins the update;
*/
struct cell {
    //! Constructor.
        /*!
          This is the constructor for a cell, that initializes all the member variables.
          \param form form name
          \param mapper mapper index
          \param field field index
          \param outCell reference to another cell, for pre-triggers; this cell is the initiator of this rule;
          \sa cell(const QString table, const size_t field)
        */
    cell(const size_t field, const QString form, size_t mapper, shared_ptr<cell> outCell):
        m_idxField(field), m_strForm(form), m_idxMapper(mapper), oCellPtr(outCell)
    {}
    //! Constructor.
        /*!
          Overriden constructor that does not need a cell reference; this is used by all rules, but pre-triggers
          \sa cell(const QString table, const size_t field, shared_ptr<cell> outCell)
        */
    cell(const size_t field, const QString form, size_t mapper):
        m_idxField(field),m_strForm(form),m_idxMapper(mapper)
    {}
   size_t              m_idxField;//!< field index (field column in the database)
   QString             m_strForm;//!< form name
   size_t              m_idxMapper;//!< mapper index

   // We wrapp the cell reference inside a smart pointer, to avoid mem leaks!
   shared_ptr<cell>    oCellPtr;//!< pointer to another cell
};

typedef shared_ptr<cell>                        cellShrPtr;//!< typedef for a smart pointer containing a cell
typedef QHash<size_t,QString>                   MapRules;//!< typedef for mapping rules (default, validation and pos-triggers)
typedef QMultiHash<size_t,shared_ptr<cell> >    MapReferences;//!< typedef for storing the references for fetching the rules

//! RuleChecker Class
/*!
This class is responsible for handling the rules from the database (storing and executing them).
In the beginning it loads all the rules into hash tables, that it searches as required; It also executes rules and returns the results;
This class should not be called directly by the UI, but through the binders.
*/
class RuleChecker: public QWidget
{
    Q_OBJECT

        public:
            //! An enum for rule types.
            /*! Types supported, as in UI_Rule_Types table, in the database: default, pre-triggers, validation and post-triggers.
            */
            enum Type { DEFAULT, /*!< Enum value for default rules. */
                        VALIDATION, /*!< Enum value for validation rules. */
                        PRETRIGGER, /*!< Enum value for rules that are triggered before the record is inserted in the database. */
                        POSTTRIGGER,/*!< Enum value for rules that are triggered after the record is inserted in the database. */
                        PRESUBMIT/*!< Enum value for rules that are triggered after the record is inserted in the database. */
                        };

            //! Constructor.
                /*!
                */
            RuleChecker(QWidget* parent=0);
            virtual ~RuleChecker();

            //! Init function
                /*!
                  This function is called after the constructor, in order to build the hash tables; it is thread-safe.
                */
            bool                init();
            //! Function that applies a Rule
                /*!
                  This function executes a query on the database; it supports the binding of a parameter, so we can cache frequent queries...
                  \param strRule rule
                  \param query reference to a query
                  \param varPar optional parameter for the query
                  \return Boolean value as success or failure
                */
            bool                applyRule(const QString strRule,QSqlQuery& query, QVariant varPar=QVariant(QVariant::Invalid));
            //! Function that parses a rule
                /*!
                  This function parses the rule string, looking for references to the state
                  of other controls; references are passed through using the reserved word
                  StrRulePtr(RULE ID);
                  We return two containers: a list of the parsed rule ids
                  and a multimap with references (table and field names); from here,
                  we can tell the binder to ask the controls for its current values, and replace them on the rule;
                  \param strRule rule
                  \param idList out: list of parsed rule ids
                  \param mapLookups out: field and table names, of the references we want to fetch
                  \return Boolean value as success or failure
                  \sa TableRuleBinder::applyRule(QString strRule, const QModelIndex& tl, const RuleChecker::Type eType, const QVariant varPar)
                */
            bool                parseRule(const QString strRule, 
                                    QMultiMap<size_t, QMap<size_t,size_t> > & mapLookups);

            // We store the rules on this containers, for rapid access: remember to redo them, when adding new rules!
            MapRules            mapDefaultRls;//!< Hash table for storing default value rules.
            MapRules            mapValidationRls;//!< Hash table for storing validation rules.
            MapRules            mapPostTriggerRls;//!< Hash table for storing post-trigger rules.
            MapRules            mapPreTriggers;//!< Hash table for storing pre-trigger value rules.
            MapRules            mapPreSubmitRls;//!< Hash table for storing pre-submit value rules.
            MapReferences       mapReferences;//!< Hash table for storing where the rules point to(it associates their id with a table name and a field index)

        public slots:

        protected:

        private:
            //! Hash Constructor
                /*!
                  This reads the different rules from the database and stores them on hash tables, so we cna have a quick access to them;
                  N.b.: it should be called, *whenever* we add/modify/delete rules on the database to reflect the changes!
                */
            bool                buildHashes();
            //! Function for Inserting a Rule
                /*!
                  This function inserts a rule reference in the references container and a rule into the hash corresponding to its type.
                  \param strRule rule
                  \param id field index
                  \param ref pointer to a cell (in the case of pre-trigger rules, where we need to know the originator)
                  \param map reference to a generic map
                  \return Boolean value as success or failure
                */
            bool                standardRuleInsertion(const QString rule, const size_t id,
                cellShrPtr ref, MapRules& ruleMap);
            //! Function that Points String to Type
                /*!
                  Convenience function for extracting the correct enum type for the rule, from a text string.
                  To make it a bit more robust, we make it case insensitive!
                  \param strType rule type as string
                  \param type reference to a rule type, where the type is gonna be written
                  \return Boolean value as success or failure
                  \sa GetContainerFromType(const Type& type)
                */
            const bool          GetTypeFromString(const QString strType, Type& type);
            //! Function that Points Type to Container
                /*!
                  Convenience Function for retrieving the correct hash table for storing a specific type.
                  \param type rule type
                  \return MapRules hash table for storing the rules
                  \sa GetTypeFromString(const QString strType, Type& type)
                */
            MapRules*           GetContainerFromType(const Type& type);
            //! Find Rule
                /*!
                  This function gets a rule ID as reference and fetches its properties
                  from the mapReferences container.
                  \param refId Rule ID
                  \param strOutField out: adress of a size_t, to put the field index
                  \return MapRules hash table for storing the rules
                  \sa parseRule(const QString strRule, QList<size_t>& idList, QMultiMap<QString, size_t>& mapLookups)
                */
            bool                findReference(const int refId, size_t& strOutField,
                QString& strOutForm, size_t& strOutMapper);

        private slots:
            //! Test
                /*!
                  This is a test function, to check if the MapReferences container
                  is empty: we cannot continue without it!
                  Watch out, because if we have a database with *NO* rules, this
                  test is gonna fail!
                  \param map address of the References map, which is suppose to be filled at this stage...
                */
            void                test(MapReferences& map);
            void                test(MapRules& map);
            void                test(const int num);

        signals:
            void                showStatus(QString str);//!< signal for showing messages in the status bar
            void                showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages
            void                done(bool bReady);
};
#endif // RULECHECKER_H

/////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef INITRULESTHREAD_H
#define INITRULESTHREAD_H

//! InitRulesThread Class
/*!
Reading the business logic from the database was taking too long, so we put it inside a thread;
Like this we still can go on with the user interface, while the app buildes the hashes (it should not take too long!)
*/

class InitRulesThread : public QThread
{
    Q_OBJECT

    public:
    //! A Constructor
    /*!
      \param parent we need to grabb a pointer to the rulechecker, so that we can initialize it inse the thread;
    */
        InitRulesThread(RuleChecker* parent);

    protected:
        void run();

    signals:
        void done(bool bOk);

    private slots:
    //! Worker Function
    /*!
      \This is where we do all the work, asynchronously;
    */
        void doTheWork();

    private:
    //! A private variable.
    /*!
      Pointer to the RuleChecker object on the main thread.
    */
        RuleChecker*                    rulesPtr;
};
#endif //INITRULESTHREAD_H
