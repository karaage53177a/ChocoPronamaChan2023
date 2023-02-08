#include "main.h"

HANDLE cmdOut;

int main() {
	cmdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
	std::cin.tie(0)->sync_with_stdio(0);
	auto videoMgr = videoManager();

	SetConsoleTextAttribute(cmdOut, CMD_WHITE);
	std::cout << "cmd���ł����\�����Ă��������I�Đ�����ESC�L�[�������ƏI�����܂��B" << std::endl;
	std::cout << "�����ł�����A�����L�[�������ĂˁB" << std::endl;
	cv::waitKey(0);
	system("cls");

	while (cv::waitKey(1) != 27) {
		if (videoMgr.GUIrender() == -1) {
			std::cout << "Video load failed." << std::endl; break;
		}
		videoMgr.CMDRender();
	}
	
	SetConsoleTextAttribute(cmdOut, CMD_WHITE);
	std::cout << std::endl << "Press any key to exit." << std::endl;
	cv::waitKey(0);
	return 0;
}

videoManager::videoManager() {
	cv::namedWindow("���傱�v���������2023", cv::WINDOW_NORMAL);
	cv::resizeWindow("���傱�v���������2023", 720, 480);
	this->setup();
}

videoManager::~videoManager() {
	if (this->video.isOpened()) this->video.release();
}

void videoManager::setup() {
	this->cmdPos.X = 0; this->cmdPos.Y = 0;
	this->video.open(this->videoPass);
	this->width = (int)this->video.get(cv::CAP_PROP_FRAME_WIDTH);
	this->height = (int)this->video.get(cv::CAP_PROP_FRAME_HEIGHT);
}

int videoManager::GUIrender() {
	if (!this->video.isOpened()) return -1;
	this->video >> this->image;
	if (this->image.empty()) {
		this->video.set(cv::CAP_PROP_POS_FRAMES, 0);
		this->video >> this->image;
	}
	cv::imshow("���傱�v���������2023", this->image);
	return 0;
}

void videoManager::CMDRender() {
	auto lastOutCol = 0;
	auto outCol = 0;
	std::string strBuf = "";

	SetConsoleCursorPosition(cmdOut, this->cmdPos);
	for (int y = 0; y < this->height; y++) {
		for (int x = 0; x < this->width * 3; x++) {
			outCol = (int)(this->image.at<uchar>(y, x) * 0.09375);
			if ((!y) && (!x)) lastOutCol = outCol;
			if (outCol == lastOutCol) strBuf += "A"; // �o�b�t�@�����O
			else { // �o��
				SetConsoleTextAttribute(cmdOut, lastOutCol);
				std::cout << strBuf;
				strBuf = "";
			}
			lastOutCol = outCol;
		}
		strBuf += "\n";
	}
}