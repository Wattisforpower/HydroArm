import ML_Model

FruitClassificationModel = ML_Model.FruitClassifier('Dataset', 200, 200, 32)

FruitClassificationModel.LoadinImages(0.2)
FruitClassificationModel.ConfigureDataset()
FruitClassificationModel.AugmentData('horizontal', 0.1, 0.1)

FruitClassificationModel.Model('relu', 'relu', 'same', 0.2)

FruitClassificationModel.TrainModel(200, 'adam')
FruitClassificationModel.PlotResults('output.png')

FruitClassificationModel.SaveModel('FruityClassifyer.tflite')
