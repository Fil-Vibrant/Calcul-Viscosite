#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    calculs.calculDelta0();
    double d0 = calculs.getD0();
    ui->label->setText(QString::number(d0));
    calculs.getDVexpValues();
    calculs.getFrequencies();
    //delta0ExpGraph();
}
/*
void Widget::delta0ExpGraph()
{
    chart = new QChart();
    serie = new QLineSeries();

    for (int i = 0; i < frequencies.size(); ++i)
    {
        serie->append(dvexp[i], frequencies[i]);
    }
    chart->addSeries(serie);
}
*/
