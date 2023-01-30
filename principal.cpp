#include "principal.h"
#include "ui_principal.h"

#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    lienzo = QPixmap(500,500);
    this->dibujar();
    ui->outCuadro->setPixmap(lienzo);
}

Principal::~Principal()
{
    delete ui;
}

void Principal::dibujar()
{
    ui->lbl_result->clear();
    lienzo.fill(Qt::white);

    QPainter painter(&lienzo);

    int x = 0;
    int y = 0;
    height_1 = ui->spinBox->value();
    height_2 = ui->spinBox_2->value();
    height_3 = ui->spinBox_3->value();

    // Crear un pincel para los bordes
    QPen pincel;
    pincel.setWidth(5);
    pincel.setColor(Qt::red);
    pincel.setJoinStyle(Qt::MiterJoin);

    // Establecer el pincel al "pintor"
    painter.setPen(pincel);

    // Dibujar primera barra
    painter.drawRect(x+50,y+(495-height_1),100,height_1);

    // Crear un objeto color para el relleno
    QColor colorRelleno(190,120,162);
    // Crear otro objeto color para el borde
    QColor colorBorde(78,3,48);

    // Cambiar el color del pincel
    pincel.setColor(colorBorde);

    // Volver a establecer el pincel al "pintor"
    painter.setPen(pincel);

    // Establecer el color al brush (relleno)
    painter.setBrush(colorRelleno);

    // Dibujar segunda barra
    painter.drawRect(x+170, y+(495-height_2), 100, height_2);

    // Creando los colores de la tercera barra
    QColor cRellenoBarra3(253, 253, 115);
    QColor cBordeBarra3(174, 174, 51);

    // Estableciendo colores al puncel y al painter
    pincel.setColor(cBordeBarra3);
    painter.setPen(pincel);
    painter.setBrush(cRellenoBarra3);

    // Dibujar tercera barra
    painter.drawRect(x+290,y+(495-height_3),100,height_3);

    double result;
    result = (height_1 + height_2 + height_3)/3;

    QPen pincel1;
    pincel1.setWidth(4);
    pincel1.setColor(Qt::magenta);
    pincel1.setJoinStyle(Qt::MiterJoin);

    // Establecer el pincel al "pintor"
    painter.setPen(pincel1);
    painter.drawLine(0,495-result,500,495-result);
    pincel1.setColor(Qt::black);
    painter.drawText(250, 492-result, QString::number(result));
    ui->lbl_result->setText("Promedio: " + QString::number(result));
    ui->outCuadro->setPixmap(lienzo);

    ui->outCuadro->setPixmap(lienzo);
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(
                this,"Guardar imagen",QString(),"Imagenes (*.png)");
    if (!nombreArchivo.isEmpty()){
        if (lienzo.save(nombreArchivo))
            QMessageBox::information(this,"Guardar imagen","Archivo guarado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,"Guardar imagen","No se pudo guardar el archivo");
    }
}


void Principal::on_spinBox_valueChanged(int arg1)
{
    dibujar();
}


void Principal::on_spinBox_2_valueChanged(int arg1)
{
    dibujar();
}


void Principal::on_spinBox_3_valueChanged(int arg1)
{
    dibujar();
}


void Principal::on_actionSalir_triggered()
{
    this->close();
}

