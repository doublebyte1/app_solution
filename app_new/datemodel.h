#ifndef DATEMODEL_H
#define DATEMODEL_H

#include <QtSql>

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//! Date Model Class
/*!
//This class implements a Model to use with the CustomTimeCtrl widget; this model represents the table "GL_Dates" on the database,
and for each record filled by the user (with local date), we need to fill the rest of the columns.
*/

class DateModel: public QSqlTableModel
{
    Q_OBJECT

    public:
		DateModel(){;}// constructor
		
        bool            insertNewRecord(const bool bAuto, const bool bDate, const bool bTime);
        void            setAuto(const bool bAuto){m_bAuto=bAuto;}
        bool            getDateTimeType( const bool bDate, const bool bTime, int& typeID);

    signals:
        void            getDateType(QModelIndex index, QVariant var) const;

    public slots:
        //! Function to listen for user dateTime type changes
        /*!
           Since the checkbox is not available for Time only widgets, the result can be only a DateTime or Date only dataType;
          \param bIsDateTime a boolean flag to set if it is DateTime
        */
         void          amendDateTimeType(bool bIsDateTime, int row);

    private:
        //! Function to retrieve the location of last inserted Session data
        /*!
          \param ID an integer memory address.
          \return Success or failure as a boolean
        */
        bool            getLocationID(int& ID);
        bool            m_bAuto;

};

#endif // DATEMODEL_H
