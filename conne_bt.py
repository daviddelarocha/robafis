"""
Projet: RobAFIS
Author: David Gustavo DE LA ROCHA RAMIREZ
"""
from typing import Any

from bluepy.btle import Peripheral

MAC_ADDR = "00:1B:10:66:6D:EB"

class BluetoothConnector(Peripheral):
	"""
	...
	"""
	def __init__(self):
		"""
		...
		"""
		super(MAC_ADDR, "public").__init__()

		self.write_service = self.getCharacteristics()[0]
	
	def write(self, msg:Any) -> None:
		"""
		...
		"""
		# self.connect(MAC_ADDR, "public")
		self.write_service.write(str(msg).encode('utf-8'))
		# self.disconnect()

	def read_confirmation(self) -> None:
		"""
		...
		"""
		# res = self.write_service.read()
		pass