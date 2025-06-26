import { Request, Response } from 'express';
import logger from '../utils/logger';

export const getHealthStatus = (req: Request, res: Response) => {
  logger.info('Health check request received');
  res.status(200).json({ status: 'ok', service: 'Saira Backend' });
};
