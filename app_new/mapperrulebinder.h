#ifndef MAPPERRULEBINDER_H
#define MAPPERRULEBINDER_H

//#include <QWidget>
#include "abstractrulebinder.h"
#include "buttongroup.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

/////////////////////////////////////////////////////////////////////////////
//! Mapper RuleBinder Class
/*!
This class implements a binder for Mappers.
The mapper contains in itself all the information about which widgets map to which fields, in the database.
*/

class MapperRuleBinder : public AbstractRuleBinder
{
    Q_OBJECT

    public:
        MapperRuleBinder( RuleChecker* ruleChecker, Sample* sample, QList<QDataWidgetMapper*> alMapper, const QString strForm, QWidget *parent = 0);
        ~MapperRuleBinder();

        QList<QDataWidgetMapper*>&     getLMapper(){return lMapper;}

    protected:
        QVariant                        getVal(const size_t field, const size_t mapper);

    private slots:
        //! Pre-Trigger Rules
        /*!
        This is an implementation of the virtual slot AbstractRuleBinder::onFireTrigger(), on the abstract class.
          \sa AbstractRuleBinder::onFireTrigger(), onFireTriggerText(const QString& text), onFireTriggerGeneric(QWidget* senderWidget, const QVariant& newValue), onFireTriggerText(const QString& text)
        */
        void                            onFireTrigger();
        //! Pre-Trigger Rules
        /*!
        This is an override, that takes text as an argument.
          \param text text changed by the event that fired this signal
          \sa onFireTrigger(), onFireTriggerText(const QString& text)
        */
        void                            onFireTriggerText(const QString& text);
        //! Exit point for Fire Trigger
        /*!
        Eventually all the fire trigger functions arrive here, after we collect the necessary arguments.
          \param senderWidget widget that triggered this function
          \param newValue value that has been assigned by the change
          \sa onFireTrigger(), onFireTriggerText(const QString& text)
        */
        void                            onFireTriggerGeneric(QWidget* senderWidget, const QVariant& newValue);

    private:
        bool                            getPreTrigger(const QVariant& newValue, QObject object, const size_t field);
        //! Connect Pre Trigger Signals
        /*!
        Implementation of the pure virtual function, in the abstract class. This function connects the specific signals for the Mapper Binder, that listen to changes in the UI.
        */
        void                            connectSignals();
        //! Function that retrieves the rules from the hash table
        /*!
        This is an implementation of the virtual function, on the abstract class.
          \param map generic rule container
          \param eType rule type
          \param varPar optional argument
          \param field field is compulsory for validation rules, but ignored on default rules
          \return Boolean value as success or failure
          \sa AbstractRuleBinder::fetchRules()
        */
        bool                            fetchRules(const MapRules& map, const RuleChecker::Type eType,
                                                const size_t mapper,int field=-1,QVariant varPar=QVariant(QVariant::Invalid));
        //! Function that applies pre-trigger
        /*!
        This is an implementation of the virtual function, on the abstract class.
          \param strRule the actual rule.
          \param newValue value changed, that triggered the rule
          \param newValue field field pointed by this rule
          \return Boolean value as success or failure
          \sa getPreTriggerGeneric(const QVariant& newValue, const size_t field)
        */
        bool                            getPreTrigger(QHash<size_t,QString>::const_iterator& rule, const QVariant& newValue, const size_t field,
            const size_t mapper);
        //! Function that Applies a Rule
        /*!
        This is the function that applies a rule to the mapper binder.
          \param strRule the actual rule
          \param aWidget widget affected by the rule
          \param eType rule type
          \param varPar optional parameter to bind to the query
          \return Boolean value as success or failure
        */
        bool                            applyRule(QHash<size_t,QString>::const_iterator& rule, QWidget* aWidget, const RuleChecker::Type eType,
            QVariant varPar=QVariant(QVariant::Invalid));
        //! Polymorphically grab the state of a widget
        /*!
        This function grabs the value of a given widget, so that we can verify it with a pre-submit rule
          \param aWidget widget from which we want to know the current value
          \param val out: address of a variant where we want to put the result (value of the widget)
          \return Boolean value as success or failure
          \sa applyRule(const QString strRule, QWidget* aWidget, const RuleChecker::Type eType, QVariant varPar=QVariant(QVariant::Invalid)),enableWidget(QWidget* aWidget, const QVariant val)
        */
        bool                            getCurrentWidgetValue(QWidget* aWidget, QVariant& val);
        //! Change the State of a Widget
        /*!
        This function enables/disables a given widget, based on a parameter (see static consts strEnable and strDisable) 
          \param aWidget widget that we want to enable/disable
          \param val string parameter to parse the state from (legal values are "ENABLE" and "DISABLE")
          \return Boolean value as success or failure
          \sa applyRule(const QString strRule, QWidget* aWidget, const RuleChecker::Type eType, QVariant varPar=QVariant(QVariant::Invalid)),getCurrentWidgetValue(QWidget* aWidget, QVariant& val)
        */
        bool                                    enableWidget(QWidget* aWidget, const QVariant val);
        //! Get Mapper from Table Name
        /*!
        This utility function find a mapper from the mapper array, that matches the given table name.
          \param strTableName table name as string
          \return QDataWidgetMapper a pointer to a QDataWidgetMapper;
        */
        QDataWidgetMapper*                      getMapperFromTable(const QString strTableName);
        QList<QDataWidgetMapper*>               lMapper;//!< Pointer to a collection of QDataWidgetMappers
};

#endif // MAPPERRULEBINDER_H
