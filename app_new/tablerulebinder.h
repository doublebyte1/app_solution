#ifndef TABLERULEBINDER_H
#define TABLERULEBINDER_HH

#include "abstractrulebinder.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! Table RuleBinder Class
/*!
This class implements a binder for Table Models.
We support pre-trigger rules, activated by changes in the individual cells and post trigger rules.
N.B.: Since the model can be a view with a filter, we support also a parameter to recreate this object on the database, when doing the query!
*/

class TableRuleBinder : public AbstractRuleBinder
{
    Q_OBJECT

    public:
        TableRuleBinder( RuleChecker* ruleChecker, QAbstractTableModel* aTable, QWidget *parent = 0);
        ~TableRuleBinder();

        QAbstractTableModel*            getModel(){return model;}

    signals:

    private slots:
        void                            onFireTrigger(){;}//!< This slot is not implemented in Table binder
        //! Slot that activates the pre-trigger rules
        /*!
        This is the override of the onFiretrigger() for Model binders: we need to retrieve an index to know where the change comes from!
          \param tl Model index of the cell that activated this signal
          \sa onFireTrigger()
        */
        void                            onFireTriggerIndex(const QModelIndex& tl);

    protected:
        QVariant                        getVal(const size_t field);

    private:
        //! Set Current Active Row
        /*!
        This function sets the current active row, so that we know which records are being edited.
        */
        void                            setCurRow(size_t row){m_curRow=row;}
        //! Get Current Active Row
        /*!
        This function is provided for convenience, for knowing which record is being edited.
        */
        size_t                          getCurRow(){return m_curRow;}//!< Retrieves current active row
        bool                            getTableName(QString& strTableName);
        //! Fetch Rules
        /*!
        N.b.: this function is *not* implemented in this class!
        */
        bool                            fetchRules(const MapRules& map, const RuleChecker::Type eType, 
            QVariant varPar=QVariant(QVariant::Invalid), int field=-1){
                (void)map; (void)eType; (void)varPar; (void)field;//The body of the function is just to remove the warnings!
                return false;}
        //! Function that Applies a Rule
        /*!
        This is the function that applies a rule to the table binder.
          \param strRule the actual rule
          \param tl model index of the modified cell
          \param eType rule type
          \param varPar optional parameter to bind to the query
          \return Boolean value as success or failure
        */
        bool                            applyRule(QString strRule, const QModelIndex& tl, const RuleChecker::Type eType, const QVariant varPar=QVariant(QVariant::Invalid));
        //! Connect Pre Trigger Signals
        /*!
        Implementation of the pure virtual function, in the abstract class. This function connects the specific signals for the Table Binder, that listen to changes in the UI.
        */
        void                            connectSignals();
        //! Function that applies pre-trigger
        /*!
        This is a implementation of the pure virtual function on the abstract class.
          \param strRule the actual rule.
          \param newValue value changed, that triggered the rule
          \param newValue field field pointed by this rule
          \return Boolean value as success or failure
          \sa AbstractRuleBinder::getPreTriggerGeneric(const QVariant& newValue, const size_t field), AbstractRuleBinder::getPreTrigger(const QString strRule, const QVariant& newValue, const size_t field)
        */
        bool                            getPreTrigger(const QString strRule, const QVariant& newValue, const size_t field);

        QAbstractTableModel*            model;//!< Pointer to a Table Model
        size_t                          m_curRow;//!< This variable stores the row that is being currently modified
};

#endif // TABLERULEBINDER_H
