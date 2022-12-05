"""
Projet: RobAFIS
Author: David Gustavo DE LA ROCHA RAMIREZ
"""
import sys
from bluepy.btle import Peripheral

MAC_ADDR = "00:1B:10:66:6D:EB"

class BluetoothConnector(Peripheral):
	"""
	...
	"""
	def __init__(self) -> None:
		super().__init__()

	