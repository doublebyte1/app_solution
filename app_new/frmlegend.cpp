#include "frmlegend.h"

FrmLegend::FrmLegend(QWidget *parent, Qt::WFlags flags):
QDialog(parent, flags){

    levels=0;
    recycled=0;
    status=0;
    root=0;
    bin=0;
    gls=0;
    ls=0;
    vessel=0;
    glsd=0;
    lsd=0;
    vesseld=0;
    merged=0;
    unmovable=0;

    setupUi(this);

    init();
}

FrmLegend::~FrmLegend()
{
    if (root!=0) delete root;
    if (bin!=0) delete bin;
    if (gls!=0) delete gls;
    if (ls!=0) delete ls;
    if (vessel!=0) delete vessel;
    if (glsd!=0) delete glsd;
    if (lsd!=0) delete lsd;
    if (vesseld!=0) delete vesseld;
    if (merged!=0) delete merged;
    if (unmovable!=0) delete unmovable;
    if (levels!=0) delete levels;
    if (recycled!=0) delete recycled;
    if (status!=0) delete status;
}

bool FrmLegend::initGenericTreeItem(const QString strTitle,
                                            const QString strDescription, QTreeWidgetItem* item)
{
     item->setText(0, strTitle);
     item->setText(1, strDescription);
     return true;
}

bool FrmLegend::initTreeChild(const QFont& font1, const QFont& font2, const QIcon& icon, const QString strTitle,
                                            const QString strDescription, QTreeWidgetItem* item)
{
    if (!initGenericTreeItem(strTitle,strDescription,item))
        return false;

    item->setIcon(0,icon);
    item->setFont(0,font1);
    item->setFont(1,font2);

    return true;
}

bool FrmLegend::initTreeParent(const QFont font, const QString strTitle,
                                            const QString strDescription, QTreeWidgetItem* item)
{
    if (!initGenericTreeItem(strTitle,strDescription,item))
        return false;

    item->setFont(0,font);

    return true;
}

void FrmLegend::init()
{
    QFont normal("Times", 10, QFont::Normal);
    QFont italic("Times", 10, -1, true);
    QFont serifFont("Times", 13, QFont::Bold);

    //TODO: return errors here!

    levels = new QTreeWidgetItem(treeWidget);
    initTreeParent(serifFont,tr("Levels"),
        tr("Different herarchical instances"),levels);

    root = new QTreeWidgetItem(levels);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/exec.png")),qApp->translate("frame", strActive)/*tr("Root")*/,
        tr("Frame Root"),root);

    bin = new QTreeWidgetItem(levels);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/trashcan.png")),qApp->translate("bin", strInactive)/*tr("Bin")*/,
        tr("Recycled Bin, where we store (permanent or temporarily) inactive instances"),bin);

    gls = new QTreeWidgetItem(levels);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/gls.png")),tr("Group of Landing Sites"),
        tr("A Group of Landing Sites, aggregating multiple landing sites"),gls);

    ls = new QTreeWidgetItem(levels);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/ls.png")),tr("Landing Site"),
        tr("A Site: can be a port, a collector vessel or simply a virtual aggregation of vessels"),ls);

    vessel = new QTreeWidgetItem(levels);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/vessel.png")),tr("Vessel"),
        tr("A vessel"),vessel);

    recycled = new QTreeWidgetItem(treeWidget);
    initTreeParent(serifFont,tr("Recycled"),
        tr("Items that are inactive (on the recycle bin)"),recycled);

    glsd = new QTreeWidgetItem(recycled);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/glsd.png")),tr("Group of Landing Sites"),
        tr("An inactive Group of Landing Sites"),glsd);

    lsd = new QTreeWidgetItem(recycled);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/lsd.png")),tr("Landing Site"),
        tr("An inactive Landing Site"),lsd);

    vesseld = new QTreeWidgetItem(recycled);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/vesseld.png")),tr("Vessel"),
        tr("An inactive vessel"),vesseld);

    status = new QTreeWidgetItem(treeWidget);
    initTreeParent(serifFont,tr("Vessel Status"),
        tr("Special statuses of the vessels, regarding different characteristics"),status);

    unmovable = new QTreeWidgetItem(status);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/vesself.png")),tr("Unmovable"),
        tr("A vessel that is flaged as unmovable (locked)"),unmovable);

    merged = new QTreeWidgetItem(status);
    initTreeChild(normal, italic,QIcon(QString::fromUtf8(":/app_new/unmovable.png")),tr("Merged"),
        tr("A vessel that is is merged from another temporary frame"),merged);

    treeWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    treeWidget->expandAll();

    for (int col=0; col < treeWidget->model()->columnCount(); ++col) {
        treeWidget->header()->setResizeMode(col,QHeaderView::ResizeToContents);
    }

}