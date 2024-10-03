import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

Window {
    id: root
    width: 1160
   height: 1010
   visible: true
   title: qsTr("Elite Corn Field Processor")

   property int gridRows: 0
   property int gridColumns: 0
   property var gridData: []

   function updateGrid() {
       gridData = cppHandler.getGrid()
       gridColumns = gridData[0].length
       gridRows = gridData.length
       console.log("Grid updated: " + gridRows + " x " + gridColumns)
       console.log("root: " + root.width + " manage: " + fieldManagement.width)
       console.log("effective width: " + (root.width - fieldManagement.width) / root.gridColumns)
   }

   RowLayout {
       spacing: 15
        ColumnLayout {
            id: fieldManagement
            spacing: 20
            implicitWidth: 150

            Column {
                Layout.fillWidth: true
                spacing: 5
                Label {
                    text: "File path"
                }

                TextField {
                    id: filePath
                    implicitWidth: 150
                    text: "../../Input2.txt"
                }

                Button {
                   text: " Field File "
                   onClicked: {
                        cppHandler.processFile(filePath.text)
                        root.updateGrid()
                   }
                }
            }

            Label {
                text: "Visible plants:\n" + cppHandler.visiblePlantsCount
            }

            Label {
                text: cppHandler.highestScore
            }

            Item { Layout.fillHeight: true }

        }
        GridLayout {
            columns: root.gridColumns
            rows: root.gridRows
            Layout.fillWidth: true
            Layout.fillHeight: true
            rowSpacing: 0
            columnSpacing: 0

            Repeater {
                model: root.gridRows * root.gridColumns  // Total number of items

                Rectangle {
                    width: (root.width - fieldManagement.width -65) / root.gridColumns // Dynamically adjust width
                    height: (root.height - 65) / root.gridRows // Dynamically adjust height

                    // Calculate a gradient gray for all hights and if the highest score color green
                    //need to check cppHandler exists so on deconstruction it doesn't become null too early
                    color: (cppHandler && Math.floor(index / root.gridColumns) === cppHandler.highestScoreX
                            && index % root.gridColumns === cppHandler.highestScoreY) ? "Green" :
                            Qt.rgba(gridData[Math.floor(index / root.gridColumns)][index % root.gridColumns] / 9,
                            gridData[Math.floor(index / root.gridColumns)][index % root.gridColumns] / 9,
                            gridData[Math.floor(index / root.gridColumns)][index % root.gridColumns] / 9, 1)
                }
            }
        }
   }
}
