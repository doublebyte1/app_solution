#ifndef ABSTRACTRULEBINDER_H
#define ABSTRACTRULEBINDER_H

#include <QObject>
#include "rulechecker.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

QString FixTableName(QString tableName);

//! Abstract RuleBinder Class
/*! This is the base class for binders that establish a connection between the rule checker and the user interface.
 All communication with the rule checker is handled by this class *only*, and the communication with the UI is established across slots and signals.
*/

class AbstractRuleBinder : public QObject
{
    Q_OBJECT

    public:
        AbstractRuleBinder( RuleChecker* ruleChecker, const QString strForm, QWidget *parent = 0);

        void                            init();
        RuleChecker*                    getRuleCheckerPtr(){return ruleCheckerPtr;}

    signals:
        void                            addRecord();//!< Signal that is emited when a new record has been initialized
        void                            defaultValuesRead();
        void                            submitRecord();//!< Signal that is emited when we are about to submit a record to the database
        void                            finishedPreSubmit(bool bOk);//!< Signal to tell the UI, that the pre submit validation is finished

        void                            showStatus(QString str);//!< Signal for messages in the status bar
        void                            showError(QString str, const bool bShowMsgBox=true);//!< Signal for errors

    protected:
        /*!
        In this function we connect all the signals responsible for the pre-triggers.
        This is to be implemented in the derived classes, since it is polymorphic.
        */
        virtual void                    connectSignals()=0;
        //! Function that applies pre-trigger
        /*!
          \param strRule the actual rule.
          \param newValue value changed, that triggered the rule
          \param newValue field field pointed by this rule
          \return Boolean value as success or failure
          \sa getPreTriggerGeneric(const QVariant& newValue, const size_t field)
        */
        virtual bool                    getPreTrigger(QHash<size_t,QString>::const_iterator& rule, const QVariant& newValue, const size_t field,
                        const size_t mapper)=0;
        //! Function that retrieves the rules from the hash table
        /*!
          \param map generic rule container
          \param eType rule type
          \param varPar optional argument
          \param field field is compulsory for validation rules, but ignored on default rules
          \return Boolean value as success or failure
        */
        virtual bool                    fetchRules(const MapRules& map, const RuleChecker::Type eType,
                                                const size_t mapper=-1, int field=-1, QVariant varPar=QVariant(QVariant::Invalid))=0;
        bool                            getValidation(const QVariant& newValue, const size_t mapper, const size_t field);
        //! Entry Point for Pre-Trigger
        /*!
        This is the generic entry for the polimorphic pre-triggers.
          \param newValue value changed, that triggered the rule
          \param field field pointed by this rule
          \return Boolean value as success or failure
          \sa getPreTrigger(const QString strRule, const QVariant& newValue, const size_t field)
        */
        bool                            getPreTriggerGeneric(const QVariant& newValue, const size_t field, const size_t mapper);
        virtual QVariant                getVal(const size_t field, const size_t mapper)=0;
        bool                            parseRuleReferences(QString& strRule);

        RuleChecker*                    ruleCheckerPtr;//!< Pointer to the rule checker
        QString                         m_strForm;

    private slots:
        //! Default Value Rules
        /*!
        This slot initializes the default values, associated to the table underlying the binder.
          \sa onFireTrigger(), onFirePostTrigger(const QString strTable, const QVariant varPar=QVariant(QVariant::Invalid))
        */
        bool                            getDefaultValues();
        //! Pre-Trigger Rules
        /*!
        This slot is connected to the specific UI signals of the binder, and it calls the pre-trigger rules.
          \sa getDefaultValues(), onFirePostTrigger(const QString strTable, const QVariant varPar=QVariant(QVariant::Invalid))
        */
        virtual void                    onFireTrigger()=0;
        //! Get Pre-submit Validation
        /*!
        This slot prompts the rulechecker to apply Pre-Submit rules
        */
        void                            getPreSubmitValidation();
};

#endif // ABSTRACTRULEBINDER_H
